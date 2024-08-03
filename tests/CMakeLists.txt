set(TEST_SOURCES
  src/main.cpp
  src/FxTest.cpp
  src/CurrencyTest.cpp)

add_executable(runTests ${TEST_SOURCES})

# add include directory
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# make link to googletest
target_link_libraries(runTests PRIVATE libfx gtest gtest_main)


include(GoogleTest)
gtest_discover_tests(runTests)
