cmake_minimum_required(VERSION 3.10)
project(Lab2_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(lab2 Threads::Threads)