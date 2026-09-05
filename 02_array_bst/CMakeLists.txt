cmake_minimum_required(VERSION 3.10)
project(array_bst)

set(CMAKE_C_STANDARD 11)

add_executable(program
        main.c
        insert.c
        auxiliary_func.c 
)