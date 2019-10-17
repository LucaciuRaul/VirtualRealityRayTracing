cmake_minimum_required(VERSION 3.15)
project(rt_incomplete)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(rt_incomplete
        Color.h
        Geometry.h
        Image.h
        Intersection.h
        Light.h
        Line.h
        lodepng.cpp
        lodepng.h
        main.cpp
        Material.h
        Scene.h
        Sphere.cpp
        Sphere.h
        Vector.h)
