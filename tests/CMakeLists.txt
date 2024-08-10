set(TEST_SOURCES
  src/main.cpp
  src/CurrencyTest.cpp
  src/FormatterTest.cpp
  src/FxTest.cpp
  src/FxInterfaceTest.cpp)

add_executable(runTests ${TEST_SOURCES})

# add include directory
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(runTests PRIVATE include)

# make link to googletest
target_link_libraries(runTests PRIVATE libfx gtest gmock)


include(GoogleTest)
gtest_discover_tests(runTests)
