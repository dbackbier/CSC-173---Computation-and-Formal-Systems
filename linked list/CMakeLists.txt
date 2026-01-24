cmake_minimum_required(VERSION 4.1)
project(linked_list C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(.)

add_executable(linked_list
        employee.c
        Employee.h
        LinkedList.c
        testLinkedList.c
        LinkedList.h)
