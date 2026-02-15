cmake_minimum_required(VERSION 4.1)
project(Project_1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(.)

add_executable(Project_1
        dfa.h
        IntHashSet.c
        IntHashSet.h
        LinkedList.c
        LinkedList.h
        nfa.h
        strdup.c
        strdup.h
        dfa.c
        nfa.c
        main.c
)
