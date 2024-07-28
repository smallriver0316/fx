# add library
add_library(fxlib Fx.cpp)


# set include directory
target_include_directories(fxlib PUBLIC ${CMAKE_SOURCE_DIR}/include)
