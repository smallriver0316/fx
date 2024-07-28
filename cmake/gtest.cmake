cmake_minimum_required(VERSION 3.16.3)

# add googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0)
FetchContent_MakeAvailable(googletest)
