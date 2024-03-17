# ThreadPool

This is a simple implementation of a thread pool in C++20.
The primary purpose of a thread pool is to improve performance and efficiency when dealing with tasks that can be executed concurrently.
Instead of creating a new thread for each task, which can be computationally expensive, a thread pool reuses a fixed number of threads to execute tasks from a queue.

### Build Instructions:

1. Make a build directory: `mkdir build && cd build`

2. Compile: `cmake .. && make`

3. Run it: `./main`
