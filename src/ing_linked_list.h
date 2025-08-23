
#pragma once

#include <stdlib.h>
#include <string.h>

#include "ing_generic_data_structures_common.h"

#define ing_linked_list(element_type) \
    ING_PRIVATE_linked_list_##element_type

#define ING_INSTANTIATE_LINKED_LIST_TEMPLATE(element_type) \
    typedef struct ing_linked_list(element_type) {         \
        struct {                                           \
            element_type value;                                \
            struct ing_linked_list(element_type)* next;   \
            void(*element_destructor)(element_type*); \
        } PRIVATE;\
        \
    } ing_linked_list(element_type);                        \
                                                           \
static inline ing_linked_list(element_type)* ING_PRIVATE_linked_list_##element_type##_init_with_value_and_element_destructor(ing_linked_list(element_type)* linked_list_ptr, element_type value, void(*element_destructor)) { \
    linked_list_ptr->PRIVATE.next = NULL;                          \
    linked_list_ptr->PRIVATE.value = value;                \
    linked_list_ptr->PRIVATE.element_destructor = element_destructor;\
                                                           \
    return linked_list_ptr;                                                           \
}                                                          \
                                                           \
                                                           \
\
static inline ing_linked_list(element_type)* ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_value_and_element_destructor(element_type value, void(*element_destructor)(element_type*)) {                                      \
    return ING_PRIVATE_linked_list_##element_type##_init_with_value_and_element_destructor(malloc(sizeof(ing_linked_list(element_type))), value, element_destructor);                                                           \
}                                                          \
                                                           \
static inline ing_linked_list(element_type)* ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_element_destructor(void(*element_destructor)(element_type*)) {                                      \
    element_type default_value;                            \
    memset(&default_value, 0, sizeof(default_value));      \
    return ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_value_and_element_destructor(default_value, element_destructor);\
    \
}                                                                   \
                                                           \
static inline void ING_PRIVATE_linked_list_append() {}                                                         \
                                                           \
\
    \
static inline void ING_PRIVATE_linked_list_##element_type##_destroy(ing_linked_list(element_type)* linked_list_ptr) {   \
    if(linked_list_ptr) {                                  \
        ING_PRIVATE_linked_list_##element_type##_destroy(linked_list_ptr->PRIVATE.next);           \
        if(linked_list_ptr->PRIVATE.element_destructor) {                           \
            linked_list_ptr->PRIVATE.element_destructor(&(linked_list_ptr->PRIVATE.value));                 \
        }\
        free(linked_list_ptr);                                                          \
    }\
}


#define ing_linked_list_create_on_heap(element_type) \
    /** if you get a compiler error here saying that the function element_type##_destroy is undefined, that means you probably want to use ing_linked_list_create_on_heap_with_nop_element_destructor instead of this */                                                                                \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_element_destructor((element_type##_destroy)))

#define ing_linked_list_create_on_heap_with_value(element_type, value) \
    /** if you get a compiler error here saying that the function element_type##_destroy is undefined, that means you probably want to use ing_linked_list_create_on_heap_with_value_and_nop_element_destructor instead of this */                                                                                      \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_value_and_element_destructor((value), (element_type##_destroy)))

#define ing_linked_list_create_on_heap_with_element_destructor(element_type, element_destructor) \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_element_destructor((element_destructor)))

#define ing_linked_list_create_on_heap_with_value_and_element_destructor(element_type, value, element_destructor) \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_value_and_element_destructor((value), (element_destructor)))

#define ing_linked_list_create_on_heap_with_nop_element_destructor(element_type) \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_element_destructor((NULL)))

#define ing_linked_list_create_on_heap_with_value_and_nop_element_destructor(element_type, value) \
    (ING_PRIVATE_linked_list_##element_type##_create_on_heap_with_value_and_element_destructor((value), (NULL)))

#define ing_linked_list_destroy(element_type, linked_list_ptr)              \
    (ING_PRIVATE_linked_list_##element_type##_destroy(linked_list_ptr))

