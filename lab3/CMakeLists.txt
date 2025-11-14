cmake_minimum_required(VERSION 3.10)
project(Lab3_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab3 src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(lab3 Threads::Threads)