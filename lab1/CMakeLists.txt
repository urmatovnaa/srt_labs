cmake_minimum_required(VERSION 3.10)
project(Lab1_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1
    src/main.cpp
    src/exercise1.cpp
    src/exercise2.cpp
    src/exercise3.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(lab1 Threads::Threads)