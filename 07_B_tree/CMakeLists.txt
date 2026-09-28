cmake_minimum_required(VERSION 3.10)
project(btree)

set(CMAKE_C_STANDARD 11)

add_executable(program
        main.c
        insert.c 
        delete.c
        print.c 
        free.c
        core.c 
        search.c 
)