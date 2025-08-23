cmake_minimum_required(VERSION 3.28)
project(ing_library_project C)

set(CMAKE_C_STANDARD 99)


add_library(ing

            ing_core_utils.c
            ing_dynamic_array.c
            ing_hash_table.c
            ing_generic_data_structures_common.h)


target_compile_definitions(ing

                           PRIVATE

                           "$<$<CONFIG:Debug>:ING_DEBUG>")


target_include_directories(ing

                           PRIVATE)

if((${CMAKE_C_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_C_COMPILER_ID} STREQUAL "Clang"))
    target_link_libraries(ing PRIVATE m)
endif()