cmake_minimum_required(VERSION 4.0)
project(P1_gruppe4 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(P1_gruppe4
        src/main.c
        src/main.h
        src/arrays.c
        src/menu.c
        src/save.c
        src/mapToLot.c
        src/parkingLot.c)
