project(Sakura)
cmake_minimum_required(VERSION 3.24)

if (WORKING_FROM_TOP_LEVEL)
    message(FATAL_ERROR "Already working from top level. If including from another project then use the Source directory.")
endif()

set(WORKING_FROM_TOP_LEVEL ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build)

include(Source/CMake_SakuraApp.txt)

add_subdirectory(Source)
