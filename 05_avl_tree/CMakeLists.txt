cmake_minimum_required(VERSION 3.10)
project(linked_bst)

set(CMAKE_C_STANDARD 11)

add_executable(program
        main.c
        insert.c 
        delete.c
        print_tree.c 
        free.c
        auxiliary_func.c
        check.c
)