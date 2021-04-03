cmake_minimum_required(VERSION 3.17)
project(MC504_projeto1 C)

set(CMAKE_C_STANDARD 99)

add_executable(MC504_projeto1 main.c sobel.c sobel.h)
target_link_libraries(MC504_projeto1 PRIVATE m)