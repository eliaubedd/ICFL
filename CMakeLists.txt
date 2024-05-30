cmake_minimum_required(VERSION 3.5)

project(ICFL)

include_directories(include)

add_executable(ICFL main.cpp
        myTree.hpp)
set_property(TARGET ICFL PROPERTY CXX_STANDARD 20)