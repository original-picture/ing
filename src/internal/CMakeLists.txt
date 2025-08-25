cmake_minimum_required(VERSION 3.28)
project(ing_internal_project C)

set(CMAKE_C_STANDARD 99)


add_library(ing_internal

            ing_core_utils.c
            ing_dynamic_array.c
            ing_hash_table.c
        ing_internal_main_loop_api.c
            ing_context.c)


if((${CMAKE_C_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_C_COMPILER_ID} STREQUAL "Clang"))
    target_link_libraries(ing_internal PRIVATE m)
endif()

target_compile_definitions(ing_internal

        PRIVATE

        "$<$<CONFIG:Debug>:ING_DEBUG>")