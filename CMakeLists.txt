cmake_minimum_required(VERSION 3.9)
project(see)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_C_COMPILER /usr/bin/musl-gcc)
#set(CMAKE_C_FLAGS "-static -Os -Wall -Werror -Wpedantic -std=c11")

add_subdirectory(src)
add_subdirectory(test)
