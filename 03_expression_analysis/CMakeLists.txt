cmake_minimum_required(VERSION 3.10)
project(03)

set(CMAKE_C_STANDARD 11)

add_executable(program
        main.c
        stack.c 
        tree.c 
        print.c
)