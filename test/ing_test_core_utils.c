
#include "ing_test_core_utils.h"

#include "ing_testing_assert.h"

#include "ing_core_utils.h"


void test_dynamic_memory() {
    int* p = ing_allocate_and_zero(sizeof(int));
    ing_testing_assert(*p == 0, "ing_allocate_and_zero actually zeroes");
}

void test_core_utils() {
    test_dynamic_memory();
}