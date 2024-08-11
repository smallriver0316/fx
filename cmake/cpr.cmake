cmake_minimum_required(VERSION 3.16.3)

# add cpr
include(FetchContent)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)
