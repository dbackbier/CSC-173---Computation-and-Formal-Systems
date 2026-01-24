cmake_minimum_required(VERSION 4.1)
project(reusable_code C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(reusable_code employee.c Employee.h employeeTest.c)
