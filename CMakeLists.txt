cmake_minimum_required(VERSION 2.8.9)
project(TaylorTrack)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
INCLUDE(FindPortaudio)
if(COMPILE_TESTCOVERAGE)
    INCLUDE(CodeCoverage)
endif()

# find YARP
find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

# find optional dependancies
find_package(OpenCV)
find_package(Portaudio)
find_package(GTest)
find_package(ZLIB)
find_package(Curses)

option(COMPILE_INPUT_DUMMY "Compile Dummy Input" OFF)
option(COMPILE_INPUT_READFILE "Compile Read File Input" OFF)
option(COMPILE_INPUT_WAVE "Compile Wave File Input" OFF)

if(PORTAUDIO_FOUND)
    include_directories(${PORTAUDIO_INCLUDE_DIRS})
    option(COMPILE_INPUT_MICROPHONE "Compile Microphone Input" ON)
else()
    message(STATUS "Portaudio not found, skipping Microphone input target")
    set(COMPILE_INPUT_MICROPHONE OFF)
endif()

if(OpenCV_FOUND)
    # If the package has been found, several variables will
    # be set, you can find the full list with descriptions
    # in the OpenCVConfig.cmake file.
    # Print some message showing some of them
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
    option(COMPILE_INPUT_OPENCV "Compile OpenCV Video Input" ON)
    option(COMPILE_TRACKER_VIDEO "Compile Vision Tracker" ON)
    if(OpenCV_VERSION VERSION_LESS "3.0.0")
        # Add OpenCV headers location to your include paths
        add_definitions(-DOLD_OPENCV_HEADERS)
    endif()
    if(CMAKE_VERSION VERSION_LESS "2.8.11")
        # Add OpenCV headers location to your include paths
        include_directories(${OpenCV_INCLUDE_DIRS})
    endif()
else()
    message(STATUS "OpenCV not found! Skipping OpenCV related targets")
    set(COMPILE_OPENCV_DATA_RECEIVER OFF)
    set(COMPILE_INPUT_OPENCV OFF)
endif()

option(COMPILE_TRACKER_AUDIO "Compile Audio Tracker" ON)

if(CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIRS})
    option(COMPILE_VISUALIZER "Visualizer" ON)
else()
    message(STATUS "Curses not found, skipping Visualizer Target")
    set(COMPILE_VISUALIZER OFF)
endif()

# find googletest
if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(GTEST_FOUND AND ZLIB_FOUND)
        option(COMPILE_TESTUNIT "Unit-Tests" OFF)
        if(COMPILE_TESTUNIT)
            option(COMPILE_TESTCOVERAGE "Test-Coverage" OFF)
        else()
            set(COMPILE_TESTCOVERAGE OFF)
        endif()
        include_directories(${ZLIB_INCLUDE_DIRS})
        include_directories(${GTEST_INCLUDE_DIRS})
    else()
        message(STATUS "GTest or Zlib not found, skipping Testunit and Coverage targets")
        set(COMPILE_TESTUNIT OFF)
        set(COMPILE_TESTCOVERAGE OFF)
    endif()
endif()

# activate debugging symbols and warnings
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -Wall -std=c++11 -g -O3")
if(COMPILE_TESTCOVERAGE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -std=c++11 -fprofile-arcs -ftest-coverage -coverage -O0")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -std=c++11 -O0")
endif()


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#add source directory
add_subdirectory(src)


