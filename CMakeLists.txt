cmake_minimum_required(VERSION 3.5)

project(ICFL)

include_directories(include)

add_executable(ICFL main.cpp
        myTree.hpp)

add_custom_command(
        TARGET ICFL
        POST_BUILD
        COMMAND leaks -atExit -- ${CMAKE_CURRENT_BINARY_DIR}/ICFL
        COMMENT "Running leaks after building ICFL"
)
set_property(TARGET ICFL PROPERTY CXX_STANDARD 20)