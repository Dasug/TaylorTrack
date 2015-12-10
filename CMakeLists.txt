cmake_minimum_required(VERSION 2.8.9)
project(TaylorTrack)

# find YARP
find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

# find googletest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
######
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest

ExternalProject_Add(gtest
        SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
        SVN_REVISION -r HEAD
        TIMEOUT 10
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND "")

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set gtest properties
ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
        )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/include")

# Download and install GoogleMock
ExternalProject_Add(
        gmock
        URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
        # Disable install step
        INSTALL_COMMAND ""
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)

# Set gmock properties
ExternalProject_Get_Property(gmock source_dir binary_dir)
set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
        )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/include")
######

# activate debugging symbols and warnings
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#add source directory
add_subdirectory(src)

