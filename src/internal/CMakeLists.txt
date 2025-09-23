cmake_minimum_required(VERSION 3.28)
project(ing_internal_project C)

set(CMAKE_C_STANDARD 99)


add_library(ing_internal
                ing_core_utils.c
                ing_dynamic_array.c
                ing_hash_table.c
                ing_hash_table_new.c
                ing_main_loop_extension_api.c
                ing_extension_api_common.c
                ing_context.c
                ing_dynamic_array_new.c)


if((${CMAKE_C_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_C_COMPILER_ID} STREQUAL "Clang"))
    target_link_libraries(ing_internal PRIVATE m)
endif()

target_compile_definitions(ing_internal

        PRIVATE

        "$<$<CONFIG:Debug>:ING_DEBUG>"
        "$<$<CONFIG:Debug>:ING_STATIC_IF_NOT_DEBUG>")