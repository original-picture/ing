
#pragma once

#include "ing_data_structures_common.h"

#include <stddef.h>

/// do NOT directly modify any members of this struct!!!
/// treat them all as purely read-only data!!
typedef struct {
    char* data;

    size_t size,
           capacity,

           sizeof_element_type;

    void(*element_destructor)(void* element);
} ing_dynamic_array;


void ING_INTERNAL_dynamic_array_init(ing_dynamic_array* da, size_t sizeof_element_type,
                                 void(*element_destructor)(void* element));

#define ing_dynamic_array_init(element_type, ing_dynamic_array_ptr, element_destructor) \
    ING_INTERNAL_dynamic_array_init(ing_dynamic_array_ptr, sizeof(element_type), element_destructor)

ing_dynamic_array* ING_INTERNAL_dynamic_array_create_on_heap(size_t sizeof_element_type,
                                                     void(*element_destructor)(void* element));

#define ing_dynamic_array_create_on_heap(element_type, element_destructor) \
    ING_INTERNAL_dynamic_array_create_on_heap(sizeof(element_type), element_destructor)

/// does NOT allocate additional space geometrically (allocates exactly as much as you ask for)
void ing_dynamic_array_reserve(ing_dynamic_array* da, size_t new_capacity);

/// allocates additional space geometrically
void ing_dynamic_array_resize(ing_dynamic_array* da, size_t new_size);

void* ING_INTERNAL_dynamic_array_at(ing_dynamic_array* da, size_t index);

#define ing_dynamic_array_at(element_type, ing_dynamic_array_ptr, size_t_index) \
    (*(element_type*)ING_INTERNAL_dynamic_array_at(ing_dynamic_array_ptr, size_t_index))

void ing_dynamic_array_push_back(ing_dynamic_array* da, void* value);

/// calls element_destructor on every element of the array, and then free's the array
/// if element_destructor is NULL, then the dynamic array's element destructor is used.
/// If the dynamic array's element destructor is NULL too, then this function does nothing
void ing_dynamic_array_destroy(ing_dynamic_array* da, void(*element_destructor)(void*));
