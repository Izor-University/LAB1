cmake_minimum_required(VERSION 4.1)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        Vector3D.c
        VectorAlgebra.cpp
        Vector3D.h
        TypeInfo.h
        TypeInfo.c)
