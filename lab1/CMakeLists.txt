cmake_minimum_required(VERSION 3.10)
project(Lab1_SRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Разные цели для Debug и Release
add_executable(lab1_debug
    src/main.cpp
    src/exercise1.cpp
    src/exercise2.cpp
    src/exercise3.cpp
)

add_executable(lab1_release
    src/main.cpp
    src/exercise1.cpp
    src/exercise2.cpp
    src/exercise3.cpp
)

# Настройки для Debug
target_compile_options(lab1_debug PRIVATE -g -O0)
target_compile_definitions(lab1_debug PRIVATE DEBUG_MODE)

# Настройки для Release
target_compile_options(lab1_release PRIVATE -O2 -DNDEBUG)

# Подключаем threading библиотеку
find_package(Threads REQUIRED)
target_link_libraries(lab1_debug Threads::Threads)
target_link_libraries(lab1_release Threads::Threads)