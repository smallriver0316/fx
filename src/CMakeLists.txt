# add library
add_library(libfx
  Fx.cpp
  FxInterface.cpp
  Currency.cpp
  Formatter.cpp)

# set include directory
target_include_directories(libfx PUBLIC ${CMAKE_SOURCE_DIR}/include)

# set target link
target_link_libraries(libfx PRIVATE cpr::cpr)
