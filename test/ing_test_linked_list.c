
#include "ing_test_linked_list.h"

#include "ing_linked_list.h"

#include "ing_testing_assert.h"

ING_INSTANTIATE_LINKED_LIST_TEMPLATE(int);

static int custom_destructor_test_value;
static void custom_destructor(int* i) {
    custom_destructor_test_value = 7;
}

static void test_create_destroy() {
    {   // with default destructor
        ing_linked_list(int)* ll = ing_linked_list_create_on_heap_with_value(int, 3);

        ing_testing_assert(ll->PRIVATE.value == 3);

        ing_linked_list_destroy(int, ll);
    }

    {   // with custom destructor
        ing_linked_list(int)* ll = ing_linked_list_create_on_heap_with_value_and_element_destructor(int, 3, custom_destructor);

        ing_testing_assert(ll->PRIVATE.value == 3);

        ing_linked_list_destroy(int, ll);

        ing_testing_assert(custom_destructor_test_value == 7);
    }
}

void test_linked_list() {
    test_create_destroy();
}
