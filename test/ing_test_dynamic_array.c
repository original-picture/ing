
#include "ing_test_dynamic_array.h"

#include "ing_dynamic_array_new.h"

#include "ing_testing_assert.h"


static void test_init() {
    {
        dynamic_array da;
        dynamic_array_init(int, &da, NULL);
    }

    {
        dynamic_array* da = dynamic_array_create_on_heap(int, NULL);
    }
}

static void test_reserve_and_resize() {
    {
        dynamic_array* da = dynamic_array_create_on_heap(int, NULL);

        dynamic_array_resize(da, 10);

        ing_testing_assert(da->size == 10);
        ing_testing_assert(da->capacity >= 10);

        for(unsigned i = 0; i < da->size; ++i) {
            ing_testing_assert(dynamic_array_at(int, da, i) == 0);
        }

        dynamic_array_at(int, da, 0) = 5;
        ing_testing_assert(dynamic_array_at(int, da, 0) == 5);

        dynamic_array_resize(da, 20);
        ing_testing_assert(dynamic_array_at(int, da, 0) == 5);
    }
}

void test_push_back_pop_back() {
    dynamic_array* da = dynamic_array_create_on_heap(int, NULL);

    dynamic_array_push_back_rvalue(int, da, 5);
    ing_testing_assert(dynamic_array_at(int, da, 0) == 5);

    dynamic_array_push_back_rvalue(int, da, 7);
    ing_testing_assert(dynamic_array_at(int, da, 0) == 5);
    ing_testing_assert(dynamic_array_at(int, da, 1) == 7);
}

void test_dynamic_array() {
    test_init();
    test_reserve_and_resize();
    test_push_back_pop_back();
}