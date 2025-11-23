cmake_minimum_required(VERSION 3.10)
project(Lab4_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab4 src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(lab4 Threads::Threads)