cmake_minimum_required(VERSION 3.10)
project(rbtree_bst)

set(CMAKE_C_STANDARD 11)

add_executable(program
        main.c
        insert.c 
        delete.c
        print.c 
        free.c
        rotate.c
        check.c
)