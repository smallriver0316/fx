cmake_minimum_required(VERSION 3.16.3)

# it enable to refer project name as ${PROJECT_NAME}
project(fx
  VERSION 0.10
  DESCRIPTION "CLI tool of converting number to foreign country style"
  LANGUAGES CXX)

# C++ version
set(CMAKE_CXX_STANDARD 17)
# output error when specified C++ version is unavailable
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ...without compiler extensions like gnu++11
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Including googletest and tests in non-Release build")
  include(cmake/gtest.cmake)
  # declare use ctest
  enable_testing()
  add_subdirectory(tests)
endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FAITAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

add_subdirectory(src)

# set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
