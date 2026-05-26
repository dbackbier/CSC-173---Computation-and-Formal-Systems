cmake_minimum_required(VERSION 4.1)
project(Project_5 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror -Wno-unused-function")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(Project_5
        main.c
        Boolean.c
        Circuit.c
        Gates.c
        strdup.c)
