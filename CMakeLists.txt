cmake_minimum_required(VERSION 3.25)
project(graph_puzzle_game_efekankvkl)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(graph_puzzle_game_efekankvkl
        AbstractGraph.cpp
        AbstractGraph.h
        Edge.cpp
        Edge.h
        EdgeList.cpp
        EdgeList.h
        main.cpp
        Path.cpp
        Path.h)
