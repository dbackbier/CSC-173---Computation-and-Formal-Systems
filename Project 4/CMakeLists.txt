cmake_minimum_required(VERSION 4.1)
project(Project_4 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(.)

add_executable(Project_4
        main.c
        string-extras.c
        string-extras.h
        hashSet.c
        hashSet.h
        database.c
        database.h)
