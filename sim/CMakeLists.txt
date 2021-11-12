# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.15)
# CMAKE_POLICY(SET CMP0072 NEW)
# Project name
project(ApogeeSim)

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories("${PROJECT_SOURCE_DIR}")


include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
		"${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
		"${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(ApogeeSim ${all_SRCS})

