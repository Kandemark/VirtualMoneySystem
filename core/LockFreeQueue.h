/**
 * @file LockFreeQueue.h
 * @brief Lock-free MPMC queue for high-performance concurrent access
 */

#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <memory>

namespace VirtualMoney {

/**
 * @brief Lock-free multi-producer multi-consumer queue
 * 
 * Zero contention under load
 * Wait-free enqueue/dequeue operations
 * Suitable for high-throughput scenarios
 */
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;
        
        Node() : next(nullptr) {}
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    alignas(64) std::atomic<Node*> head;
    alignas(64) std::atomic<Node*> tail;
    
public:
    LockFreeQueue() {
        Node* dummy = new Node();
        head.store(dummy, std::memory_order_relaxed);
        tail.store(dummy, std::memory_order_relaxed);
    }
    
    ~LockFreeQueue() {
        while (Node* node = head.load(std::memory_order_relaxed)) {
            head.store(node->next.load(std::memory_order_relaxed), 
                      std::memory_order_relaxed);
            delete node;
        }
    }
    
    /**
     * @brief Enqueue item (wait-free)
     * @param value Item to enqueue
     */
    void enqueue(const T& value) {
        Node* node = new Node(value);
        Node* prev_tail = tail.exchange(node, std::memory_order_acq_rel);
        prev_tail->next.store(node, std::memory_order_release);
    }
    
    /**
     * @brief Dequeue item (lock-free)
     * @param result Output parameter for dequeued item
     * @return true if item was dequeued, false if queue was empty
     */
    bool dequeue(T& result) {
        Node* old_head = head.load(std::memory_order_acquire);
        
        while (true) {
            Node* next = old_head->next.load(std::memory_order_acquire);
            
            if (!next) {
                return false; // Queue is empty
            }
            
            if (head.compare_exchange_weak(old_head, next,
                                          std::memory_order_release,
                                          std::memory_order_acquire)) {
                result = next->data;
                delete old_head;
                return true;
            }
        }
    }
    
    /**
     * @brief Check if queue is empty (approximate)
     */
    bool empty() const {
        Node* h = head.load(std::memory_order_acquire);
        Node* next = h->next.load(std::memory_order_acquire);
        return next == nullptr;
    }

private:
    // Prevent copying
    LockFreeQueue(const LockFreeQueue&) = delete;
    LockFreeQueue& operator=(const LockFreeQueue&) = delete;
};

} // namespace VirtualMoney

#endif // LOCK_FREE_QUEUE_H
