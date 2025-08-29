
#include "ing_hash_table_new.h"

#include <stdlib.h>
#include <string.h>

void hash_table_init(hash_table* ht, size_t sizeof_element_type,
                     void(*hash_function)(void* element, size_t sizeof_element_type),
                     void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                     void(*element_destructor)(void* element, size_t sizeof_element_type)) {

    memset(ht, 0, sizeof(*ht));
    ht->sizeof_element_type = sizeof_element_type;
}

hash_table hash_table_create(size_t sizeof_element_type,
                             void(*hash_function)(void* element, size_t sizeof_element_type),
                             void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                             void(*element_destructor)(void* element, size_t sizeof_element_type)) {

    hash_table ret;
    hash_table_init(&ret, sizeof_element_type);

    return ret;
}

hash_table* hash_table_create_on_heap(size_t sizeof_element_type,
                                      void(*hash_function)(void* element, size_t sizeof_element_type),
                                      void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                                      void(*element_destructor)(void* element, size_t sizeof_element_type)) {

    hash_table* ret = malloc(sizeof(hash_table));
    hash_table_init(ret, sizeof_element_type, hash_function, is_equal, element_destructor);

    return ret;
}