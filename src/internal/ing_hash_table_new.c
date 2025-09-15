
#include "ing_hash_table_new.h"

#include "ing_core_utils.h"

#include <stdlib.h>
#include <string.h>

size_t ing_default_hash (void* element, size_t sizeof_element_type) {
    ing_internal_assert(sizeof_element_type <= sizeof(size_t));

    size_t ret = 0;
    memcpy(&ret, element, sizeof(element));
    return ret;
}

bool ing_default_is_equal(void* a, void* b, size_t sizeof_element_type) {
    return (memcmp(a, b, sizeof_element_type) == 0);                                                                               \
}

void ING_INTERNAL_hash_table_init(ing_hash_table* ht, size_t sizeof_element_type,
                                  void(*hash_function)(void* element),
                                  void(*is_equal)(void* element_a, void* element_b),
                                  void(*element_destructor)(void* element)) {

    memset(ht, 0, sizeof(*ht));
    ING_INTERNAL_dynamic_array_init(&ht->array_of_linked_list, sizeof_element_type, element_destructor);
}

ing_hash_table ING_INTERNAL_hash_table_create(size_t sizeof_element_type,
                                              void(*hash_function)(void* element),
                                              void(*is_equal)(void* element_a, void* element_b),
                                              void(*element_destructor)(void* element)) {

    ing_hash_table ret;
    ING_INTERNAL_hash_table_init(&ret, sizeof_element_type,
                    hash_function,
                    is_equal,
                    element_destructor);

    return ret;
}

ing_hash_table* ING_INTERNAL_hash_table_create_on_heap(size_t sizeof_element_type,
                                                       void(*hash_function)(void* element),
                                                       void(*is_equal)(void* element_a, void* element_b),
                                                       void(*element_destructor)(void* element)) {

    ing_hash_table* ret = malloc(sizeof(ing_hash_table));
    ING_INTERNAL_hash_table_init(ret, sizeof_element_type, hash_function, is_equal, element_destructor);

    return ret;
}