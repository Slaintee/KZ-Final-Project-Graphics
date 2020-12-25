cmake_minimum_required(VERSION 3.16)
project(KZ-Final-Project-Graphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(KZ-Final-Project-Graphics
        Camera.h
        Collisions.h
        Objects.cpp
        Objects.h
        Rays.cpp
        Rays.h
        RayTraceDemo.cpp
        Scene.h
        Vector3.cpp
        Vector3.h)
