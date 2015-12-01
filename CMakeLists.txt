cmake_minimum_required(VERSION 2.8.9)
project(TaylorTrack)

# find YARP
find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

# activate debugging symbols and warnings
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#add source directory
add_subdirectory(src)
