cmake_minimum_required(VERSION 3.9)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

# Prepare the catch library.
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable.
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp bigint/bigint.cpp bigint/bigint.h)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch)