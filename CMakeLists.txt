cmake_minimum_required(VERSION 4.1)
project(UniversityHW C)

set(CMAKE_C_STANDARD 11)

include_directories(ex1)

add_executable(UniversityHW
        ex1/cipher.c
        ex1/cipher.h
        ex1/main.c
        ex1/tests.c
        ex1/tests.h)
