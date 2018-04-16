cmake_minimum_required(VERSION 3.10)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

add_executable(checkers main.cpp
        checkersMinMax.cpp checkersMinMax.hpp
        types.hpp
        node.cpp node.hpp)
