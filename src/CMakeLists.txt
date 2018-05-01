cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ant.cpp
        ant.h
        game.cpp
        genome.h
        Makefile
        map.cpp
        map.h
        net.cpp
        net.h
        objects.cpp
        objects.h
        renderable.h
        renderer.cpp
        renderer.h
        shader.cpp
        shader.h
        stdGL.h
        test.cpp
        text.cpp
        text.h
        tile.cpp
        tile.h)

add_executable(src ${SOURCE_FILES})