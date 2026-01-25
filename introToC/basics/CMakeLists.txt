cmake_minimum_required(VERSION 4.1)
project(basics C)

set(CMAKE_C_STANDARD 11)

add_executable(basics main.c)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)
