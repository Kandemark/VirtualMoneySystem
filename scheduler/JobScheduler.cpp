#include "JobScheduler.h"
#include <iostream>
#include <algorithm>

JobScheduler::JobScheduler() : running(false) {}

JobScheduler::~JobScheduler() {
    stop();
}

void JobScheduler::start() {
    if (running) return;
    running = true;
    workerThread = std::thread(&JobScheduler::run, this);
}

void JobScheduler::stop() {
    if (!running) return;
    running = false;
    cv.notify_all();
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void JobScheduler::schedule(Job job, int intervalSeconds) {
    std::lock_guard<std::mutex> lock(mtx);
    jobs.push_back({job, intervalSeconds, std::chrono::steady_clock::now() + std::chrono::seconds(intervalSeconds)});
    cv.notify_one();
}

void JobScheduler::run() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if (jobs.empty()) {
            cv.wait(lock, [this] { return !running || !jobs.empty(); });
        } else {
            // Find the job with the earliest next run time
            auto earliestJobIt = std::min_element(jobs.begin(), jobs.end(), 
                [](const ScheduledJob& a, const ScheduledJob& b) {
                    return a.nextRun < b.nextRun;
                });

            auto now = std::chrono::steady_clock::now();
            if (earliestJobIt->nextRun <= now) {
                // Run the job
                // Unlock while running the job to avoid blocking schedule()
                Job jobToRun = earliestJobIt->job;
                
                // Update next run time
                earliestJobIt->nextRun = now + std::chrono::seconds(earliestJobIt->intervalSeconds);
                
                lock.unlock();
                try {
                    jobToRun();
                } catch (const std::exception& e) {
                    std::cerr << "Job failed: " << e.what() << std::endl;
                }
                lock.lock();
            } else {
                cv.wait_until(lock, earliestJobIt->nextRun);
            }
        }
    }
}
