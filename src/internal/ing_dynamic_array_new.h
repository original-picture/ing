
#pragma once

#include <stddef.h>

typedef struct {
    char* data;

    size_t size,
           capacity,

           sizeof_element_type;

    void(*element_destructor)(void* element);
} dynamic_array;


void INTERNAL_dynamic_array_init(dynamic_array* da, size_t sizeof_element_type,
                                 void(*element_destructor)(void* element));

#define dynamic_array_init(element_type, dynamic_array_ptr, element_destructor) \
    INTERNAL_dynamic_array_init(dynamic_array_ptr, sizeof(element_type), element_destructor)

dynamic_array* INTERNAL_dynamic_array_create_on_heap(size_t sizeof_element_type,
                                                     void(*element_destructor)(void* element));

#define dynamic_array_create_on_heap(element_type, element_destructor) \
    INTERNAL_dynamic_array_create_on_heap(sizeof(element_type), element_destructor)

/// does NOT allocate additional space geometrically (allocates exactly as much as you ask for)
void dynamic_array_reserve(dynamic_array* da, size_t new_capacity);

/// allocates additional space geometrically
void dynamic_array_resize(dynamic_array* da, size_t new_size);

void* INTERNAL_dynamic_array_at(dynamic_array* da, size_t index);

#define dynamic_array_at(element_type, dynamic_array_ptr, size_t_index) \
    (*(element_type*)INTERNAL_dynamic_array_at(dynamic_array_ptr, size_t_index))

void dynamic_array_push_back(dynamic_array* da, void* value);

#define make_lvalue(type, rvalue_expression) ((type){rvalue_expression})

#define dynamic_array_push_back_rvalue(element_type, dynamic_array_ptr, rvalue_expression) \
    dynamic_array_push_back((dynamic_array_ptr), &make_lvalue(element_type, rvalue_expression))

