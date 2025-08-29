
#pragma once

#include <stddef.h>

typedef struct {
    char* data;

    size_t size,
           capacity,

           sizeof_element_type;

    void(*element_destructor)(void* element);

    #ifdef ING_DEBUG
        const char* element_typename;
    #endif
} dynamic_array;


void INTERNAL_dynamic_array_init(dynamic_array * ht, size_t sizeof_element_type,
                        void(*element_destructor)(void* element)
                        #ifdef ING_DEBUG
                            , const char* element_typename
                        #endif
                        );

dynamic_array* INTERNAL_dynamic_array_create_on_heap(size_t sizeof_element_type,
                                      void(*element_destructor)(void* element));

/// does NOT allocate additional space geometrically (allocates exactly as much as you ask for)
void dynamic_array_reserve(dynamic_array* da, size_t new_capacity);

/// allocates additional space geometrically
void dynamic_array_resize(dynamic_array* da, size_t new_size);

void* INTERNAL_dynamic_array_at(dynamic_array* da, size_t index
                                #ifdef ING_DEBUG
                                    , const char* element_typename
                                #endif
                                );


void INTERNAL_dynamic_array_push_back(dynamic_array* da, void* value
                                      #ifdef ING_DEBUG
                                          , const char* element_typename
                                      #endif
                                      );

#ifdef ING_DEBUG
    #define dynamic_array_at(element_type, dynamic_array_ptr, size_t_index) \
        (*(element_type*)INTERNAL_dynamic_array_at(dynamic_array_ptr, size_t_index, #element_type))

    #define dynamic_array_push_back(element_type, dynamic_array_ptr, void_ptr_value) \
        INTERNAL_dyanmic_array_push_back(dynamic_array_ptr, void_ptr_value, #element_type)
#else

#endif

#define make_lvalue(type, expression) (&((type)(expression)))
