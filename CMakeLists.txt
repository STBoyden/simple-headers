cmake_minimum_required(VERSION 3.17)
project(simple_headers C)

add_compile_definitions(DEBUG)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(simple_headers
        hashmap.h
        hashmap.c
        main.c
        sstring.h
        types.h
        types.c
        vector.h
        vector.c)
