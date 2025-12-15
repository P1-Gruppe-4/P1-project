cmake_minimum_required(VERSION 4.0)
project(P1_gruppe4 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(P1_gruppe4
        src/main.c
        src/types.h
        src/arrays.c
        src/menu.c
        src/save.c
        src/map_to_lot.c
        src/parking_lot.c
        src/find.c
        src/delete.c)
