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
set(SOURCES
    src/main.cpp
    src/Fx.cpp)

# define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FAITAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# set include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
