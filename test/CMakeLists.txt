cmake_minimum_required(VERSION 3.14)

include(FetchContent)

# add gtest
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.11.0 
)

set(CMAKE_CXX_STANDARD 11)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(BINARY ${CMAKE_PROJECT_NAME}_test)
add_executable(${BINARY} test.cpp)

target_link_libraries(${BINARY} PUBLIC
	gtest
	gtest_main
	${CMAKE_PROJECT_NAME}_lib
)

add_test(
	NAME ${BINARY}
	COMMAND ${BINARY}
)