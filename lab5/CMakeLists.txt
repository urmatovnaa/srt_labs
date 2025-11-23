cmake_minimum_required(VERSION 3.10)
project(Lab5_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab5 src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(lab5 Threads::Threads)