cmake_minimum_required(VERSION 3.23)
project(OptmizationSearchAlgorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(OptmizationSearchAlgorithms main.c
        TrepaColinas.c
        TrepaColinas.h
        Genetico.c
        Genetico.h
        files.c
        files.h
        utils.c
        utils.h)
