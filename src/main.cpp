#include "ThreadPool.h"
#include <iostream>

int main() {
    ThreadPool pool(4);  // create a pool with 4 threads

    // add tasks to the pool
    for (int i = 1; i <= 10; ++i) {
        pool.addTask([i]() {
            const auto s = "Running task " + std::to_string(i) + "\n";
            std::cout << s;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
