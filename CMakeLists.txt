cmake_minimum_required(VERSION 3.7)
project(Project1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(Project1 ${SOURCE_FILES})
add_executable(main main.c)