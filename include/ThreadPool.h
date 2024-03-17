#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

class ThreadPool final
{
public:
    using TaskType = std::function<void()> ;

    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    void addTask(const TaskType& task);
    void addTask(TaskType&& task);

private:
    std::deque<TaskType> queue_;
    std::mutex queueMutex_;
    std::vector<std::jthread> threads_;
    std::condition_variable condQueueNotEmpty;

    template<typename T>
    void add(T&& task)
    {
        {
            std::lock_guard lock(queueMutex_);
            queue_.push_back(std::forward<T>(task));
        }

        condQueueNotEmpty.notify_one();
    }
};
