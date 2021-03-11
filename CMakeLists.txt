cmake_minimum_required(VERSION 3.17)
project(simple_headers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(simple_headers
        collections.h
        dictionary.h
        main.c
        sstring.h
        types.h
        vec.h)
