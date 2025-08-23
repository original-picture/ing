
cmake_minimum_required(VERSION 3.28)
project(ing_test_project C)

set(CMAKE_C_STANDARD 99)


add_executable(ing_test

               ing_test_main.c

               ing_test_core_utils.c
               ing_test_dynamic_array.c
               ing_test_hash_table.c
        ing_test_linked_list.c)


include(CTest)

add_test(ing_ctest ing_test)

target_compile_definitions(ing_test
        PRIVATE

        "$<$<CONFIG:Debug>:ING_DEBUG>")
