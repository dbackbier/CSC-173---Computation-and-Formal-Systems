cmake_minimum_required(VERSION 4.1)
project(binary_search_tree C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(binary_search_tree
        main.c)
