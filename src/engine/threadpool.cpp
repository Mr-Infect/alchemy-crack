#include "engine/threadpool.hpp"

ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this]() {
            while (!stop) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);

                    condition.wait(lock, [this]() {
                        return stop || !tasks.empty();
                    });

                    if (stop && tasks.empty())
                        return;

                    task = std::move(tasks.front());
                    tasks.pop();
                }

                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace(task);
    }
    condition.notify_one();
}

void ThreadPool::shutdown() {
    stop = true;
    condition.notify_all();
}

ThreadPool::~ThreadPool() {
    shutdown();
    for (std::thread &worker : workers)
        worker.join();
}
