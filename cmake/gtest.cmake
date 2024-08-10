cmake_minimum_required(VERSION 3.16.3)

# add googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON)
set(BUILD_GMOCK ON)

FetchContent_MakeAvailable(googletest)
