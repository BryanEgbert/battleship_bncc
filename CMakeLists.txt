cmake_minimum_required(VERSION 3.14)
project(battleship VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)


enable_testing()

add_subdirectory(src)
add_subdirectory(test)
include(CPack)

