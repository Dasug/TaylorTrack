cmake_minimum_required(VERSION 2.8.9)
project(TaylorTrack)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
INCLUDE(CodeCoverage)

# find YARP
find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

# find OpenCV
find_package(OpenCV REQUIRED)
# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
    # Add OpenCV headers location to your include paths
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

# find googletest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# activate debugging symbols and warnings
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -g -O0 -fprofile-arcs -ftest-coverage -coverage")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#add source directory
add_subdirectory(src)

