cmake_minimum_required(VERSION 3.20)
project(ee332 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_program main.cpp bmp.cpp)

target_compile_options(my_program PRIVATE -Wall -Wextra -g)

target_link_options(my_program PRIVATE -static)

add_custom_target(run
    COMMAND my_program
    DEPENDS my_program)
