cmake_minimum_required(VERSION 3.10)
project(Lab6_SRT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(exercise1 src/exercise1.cpp)
add_executable(exercise2 src/exercise2.cpp)

find_package(Threads REQUIRED)
target_link_libraries(exercise1 Threads::Threads)
target_link_libraries(exercise2 Threads::Threads)