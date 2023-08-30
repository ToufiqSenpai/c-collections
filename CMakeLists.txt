cmake_minimum_required(VERSION 3.26)
project(collection C)

set(CMAKE_C_STANDARD 17)
add_library(collection_library
        src/list.c
        src/linkedlist.c
        src/linkedlist.h
        src/linkedlist.h)

target_include_directories(collection_library PUBLIC src/common.h src/list.h)
add_executable(collection_test tests/list.c)
