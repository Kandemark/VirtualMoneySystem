#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class JobScheduler {
public:
    using Job = std::function<void()>;

    JobScheduler();
    ~JobScheduler();

    void start();
    void stop();
    void schedule(Job job, int intervalSeconds);

private:
    struct ScheduledJob {
        Job job;
        int intervalSeconds;
        std::chrono::steady_clock::time_point nextRun;
    };

    std::vector<ScheduledJob> jobs;
    std::thread workerThread;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> running;

    void run();
};

#endif // JOB_SCHEDULER_H
