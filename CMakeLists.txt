cmake_minimum_required(VERSION 3.17)
project(Mat_log)

set(CMAKE_CXX_STANDARD 14)

link_libraries(/Users/astra/Documents/6_sem/Mat_log/libbdd.a)
include_directories(/Users/astra/Documents/6_sem/Mat_log/src)

add_executable(Mat_log main.cpp utils.hpp limit.hpp)