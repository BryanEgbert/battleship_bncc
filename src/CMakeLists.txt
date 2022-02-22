cmake_minimum_required(VERSION 3.0.0)
project(battleship VERSION 0.1.0)

add_executable(battleship main.c battleship.h battleship.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
