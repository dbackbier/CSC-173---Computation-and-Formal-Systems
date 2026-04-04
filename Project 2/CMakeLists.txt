cmake_minimum_required(VERSION 4.1)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(.)

add_executable(Project_2
        main.c
        stack.c
        stack.h
        parsetree.c
        parsetree.h
        recursive-descent-parser.c
        recursive-descent-parser.h
        table-driven-parser.c
        table-driven-parser.h
        queue.c
        queue.h)
