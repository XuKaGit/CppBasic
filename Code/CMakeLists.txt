cmake_minimum_required(VERSION 3.10.0)
project(CppBasic VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(CppBasic main.cpp)

