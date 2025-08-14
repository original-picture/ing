cmake_minimum_required(VERSION 3.31)
project(ing_project C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(ing_test PRIVATE ing)
target_include_directories(ing_test PRIVATE src)