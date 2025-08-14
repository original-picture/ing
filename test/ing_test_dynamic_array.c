
#include "ing_test_dynamic_array.h"

#include "ing_dynamic_array.h"

#include "ing_testing_assert.h"

ING_INSTANTIATE_DYNAMIC_ARRAY_TEMPLATE(int);

static void test_init() {
    {
        ing_dynamic_array(int) arr = ing_dynamic_array_create(int);

        ing_testing_assert(arr.PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size     == 0);
        ing_testing_assert(arr.PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 0);
    }

    {
        ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size     == 0);
        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 0);
    }

    {
        ing_dynamic_array(int) arr;

        ing_dynamic_array_init(&arr);

        ing_testing_assert(arr.PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size     == 0);
        ing_testing_assert(arr.PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 0);

        ing_dynamic_array_deinit(&arr);
    }
}

static void test_reserve_and_resize() {
   {
       ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

       ing_dynamic_array_reserve(arr, 10);

       ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 10);
   }

   {
       ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

       ing_dynamic_array_resize(arr, 10);

       ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 10);
       ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size     == 10);

       for(int i = 0; i < 10; ++i) {
           ing_testing_assert(arr->arr[i] == 0, "resize actually zeroes the new memory");
       }

       arr->arr[0] = 1;
       arr->arr[1] = 2;

       ing_dynamic_array_resize(arr, 100);

       ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity == 100);
       ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size     == 100);

       ing_testing_assert(arr->arr[0] == 1, "resize doesn't trash existing values");
       ing_testing_assert(arr->arr[1] == 2, "resize doesn't trash existing values");

       for(int i = 2; i < arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size; ++i) {
           ing_testing_assert(arr->arr[i] == 0, "resize actually zeroes the new memory");
       }

   }
}

void test_push_back_pop_back() {
    {
        ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

        ing_dynamic_array_int_push_back(arr, 5);

        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size == 1);
        ing_testing_assert(arr->arr[0] == 5);

        ing_dynamic_array_int_push_back(arr, 7);

        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size == 2);
        ing_testing_assert(arr->arr[0] == 5);
        ing_testing_assert(arr->arr[1] == 7);


        ing_dynamic_array_resize(arr, 10);

        ing_testing_assert(arr->arr[0] == 5);
        ing_testing_assert(arr->arr[1] == 7);

        ing_dynamic_array_resize(arr, 2);

        ing_testing_assert(arr->arr[0] == 5);
        ing_testing_assert(arr->arr[1] == 7);

        ing_dynamic_array_pop_back(arr);
        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size == 1);

        ing_dynamic_array_pop_back(arr);
        ing_testing_assert(arr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size == 0);
    }
}

void test_dynamic_array() {
    test_init();
    test_reserve_and_resize();
}