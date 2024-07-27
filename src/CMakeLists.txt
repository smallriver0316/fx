# define the executable
add_executable(${PROJECT_NAME} main.cpp Fx.cpp)

# set include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
