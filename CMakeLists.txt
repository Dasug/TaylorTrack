cmake_minimum_required(VERSION 2.8.9)
project(TaylorTrack)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
INCLUDE(CodeCoverage)

# find YARP
find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

# find googletest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# activate debugging symbols and warnings
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#add source directory
add_subdirectory(src)

