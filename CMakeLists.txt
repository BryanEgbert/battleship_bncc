cmake_minimum_required(VERSION 3.0.0)
project(battleship VERSION 0.1.0)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
include(CPack)

