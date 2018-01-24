cmake_minimum_required(VERSION 3.9)
project(see)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER /usr/bin/musl-gcc)
set(CMAKE_C_FLAGS "-static -Os")

add_executable(see src/main.c)
