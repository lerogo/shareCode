cmake_minimum_required(VERSION 3.19)
project(image_processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_processing main.cpp bmp_file/bmp_file_process.hpp bmp_file/bmp_file_info.h bmp_file/bmp_file.hpp)
