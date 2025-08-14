cmake_minimum_required(VERSION 3.31)
project(ing_library_project C)

set(CMAKE_C_STANDARD 99)


add_library(ing

            ing_core_utils.c
            ing_dynamic_array.c)


target_compile_definitions(ing

                           PRIVATE

                           "$<$<CONFIG:Debug>:ING_DEBUG>")


target_include_directories(ing

                           PRIVATE)

