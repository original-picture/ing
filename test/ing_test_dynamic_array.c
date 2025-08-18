
#include "ing_test_dynamic_array.h"

#include "ing_dynamic_array.h"

#include "ing_testing_assert.h"

ING_INSTANTIATE_DYNAMIC_ARRAY_TEMPLATE(int);

static void test_init() {
    {
        ing_dynamic_array(int) arr = ing_dynamic_array_create(int);

        ing_testing_assert(arr.PRIVATE.size     == 0);
        ing_testing_assert(arr.PRIVATE.capacity == 0);
    }

    {
        ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

        ing_testing_assert(arr->PRIVATE.size     == 0);
        ing_testing_assert(arr->PRIVATE.capacity == 0);
    }

    {
        ing_dynamic_array(int) arr;

        ing_dynamic_array_init(int, &arr);

        ing_testing_assert(arr.PRIVATE.size     == 0);
        ing_testing_assert(arr.PRIVATE.capacity == 0);

        ing_dynamic_array_deinit(int, &arr);
    }
}

static void test_reserve_and_resize() {
   {
       ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

       ing_dynamic_array_reserve(int, arr, 10);

       ing_testing_assert(arr->PRIVATE.capacity >= 10);
   }

   {
       ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

       ing_dynamic_array_resize(int, arr, 10);

       ing_testing_assert(arr->PRIVATE.capacity >= 10);
       ing_testing_assert(arr->PRIVATE.size     == 10);

       for(int i = 0; i < 10; ++i) {
           ing_testing_assert(arr->PRIVATE.arr[i] == 0, "resize actually zeroes the new memory");
       }

       arr->PRIVATE.arr[0] = 1;
       arr->PRIVATE.arr[1] = 2;

       ing_dynamic_array_resize(int, arr, 100);

       ing_testing_assert(arr->PRIVATE.capacity >= 100);
       ing_testing_assert(arr->PRIVATE.size     == 100);

       ing_testing_assert(arr->PRIVATE.arr[0] == 1, "resize doesn't trash existing values");
       ing_testing_assert(arr->PRIVATE.arr[1] == 2, "resize doesn't trash existing values");

       for(int i = 2; i < arr->PRIVATE.size; ++i) {
           ing_testing_assert(arr->PRIVATE.arr[i] == 0, "resize actually zeroes the new memory");
       }

   }
}

void test_push_back_pop_back() {
    {
        ing_dynamic_array(int)* arr = ing_dynamic_array_create_on_heap(int);

        ing_dynamic_array_push_back(int, arr, 5);

        ing_testing_assert(arr->PRIVATE.size == 1);
        ing_testing_assert(arr->PRIVATE.arr[0] == 5);

        ing_dynamic_array_push_back(int, arr, 7);

        ing_testing_assert(arr->PRIVATE.size == 2);
        ing_testing_assert(arr->PRIVATE.arr[0] == 5);
        ing_testing_assert(arr->PRIVATE.arr[1] == 7);


        ing_dynamic_array_resize(int, arr, 10);

        ing_testing_assert(arr->PRIVATE.arr[0] == 5);
        ing_testing_assert(arr->PRIVATE.arr[1] == 7);

        ing_dynamic_array_resize(int, arr, 2);

        ing_testing_assert(arr->PRIVATE.arr[0] == 5);
        ing_testing_assert(arr->PRIVATE.arr[1] == 7);

        ing_dynamic_array_pop_back(int, arr);
        ing_testing_assert(arr->PRIVATE.size == 1);

        ing_dynamic_array_pop_back(int, arr);
        ing_testing_assert(arr->PRIVATE.size == 0);
    }
}

void test_dynamic_array() {
    test_init();
    test_reserve_and_resize();
}