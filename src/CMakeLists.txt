cmake_minimum_required(VERSION 3.14)
project(${CMAKE_PROJECT_NAME} VERSION 0.1.0)

set(FILE "main.c" "battleship.h" "battleship.c")

add_executable(${CMAKE_PROJECT_NAME}_exe ${FILE})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${FILE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
