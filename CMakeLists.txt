cmake_minimum_required(VERSION 3.10)
project(http_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(http_server main.cpp server.cpp server.h http.cpp http.h file.cpp file.h defines.h)