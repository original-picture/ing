
cmake_minimum_required(VERSION 3.28)
project(ing_examples_project C)

set(CMAKE_C_STANDARD 99)


add_executable(0_ing_hello_window

               0_ing_hello_window.c)

# the ing library is linked in the top-level CMakeLists.txt
