cmake_minimum_required(VERSION 3.28)
project(ing_project C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

target_include_directories(ing_internal PRIVATE include/extension)

target_include_directories(ing PUBLIC  include)
target_include_directories(ing PRIVATE include/extension)

target_link_libraries(ing_test PRIVATE ing_internal)
target_include_directories(ing_test PRIVATE src/internal)

target_link_libraries(0_ing_hello_window PRIVATE ing)
# the ing library exposes its public include directories, so there's no need to do target_include_directories