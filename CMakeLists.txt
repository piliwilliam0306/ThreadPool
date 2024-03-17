cmake_minimum_required(VERSION 3.10)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(ThreadPool src/ThreadPool.cpp include/ThreadPool.h)

add_executable(main src/main.cpp)
target_link_libraries(main ThreadPool)
