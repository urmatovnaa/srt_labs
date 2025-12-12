cmake_minimum_required(VERSION 3.10)
project(TCP_Sockets)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tcp_client TCPClient.cpp)
add_executable(tcp_server TCPServer.cpp)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tcp_client PRIVATE -Wall)
    target_compile_options(tcp_server PRIVATE -Wall)
endif()

set_target_properties(tcp_client tcp_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)