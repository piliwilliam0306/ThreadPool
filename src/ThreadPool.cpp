#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount) :
    threads_(threadCount == 0 ? std::thread::hardware_concurrency() : threadCount)
{
    for (auto& t : threads_)
    {
        t = std::jthread([this](std::stop_token token)
        {
            while (!token.stop_requested())
            {
                TaskType task;
                {
                    std::unique_lock lock(queueMutex_);
                    condQueueNotEmpty.wait(lock, [this, token]()
                    {
                        return !queue_.empty() || token.stop_requested();
                    });

                    if (token.stop_requested())
                    {
                        return;
                    }

                    task = std::move(queue_.front());
                    queue_.pop_front();
                }

                if (task)
                {
                    if (token.stop_requested())
                    {
                        return;
                    }

                    task();
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    for (auto& t : threads_) {
        t.request_stop();
    }

    condQueueNotEmpty.notify_all();
}

void ThreadPool::addTask(const TaskType& task) {
    add(task);
}

void ThreadPool::addTask(TaskType&& task) {
    add(std::move(task));
}
