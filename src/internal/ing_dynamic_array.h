
#pragma once

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ing_core_utils.h"

#include "ing_generic_data_structures_common.h"



#define ing_dynamic_array(element_type, /*hash_function*/...) \
    ING_PRIVATE_dynamic_array_##element_type

#define ING_INSTANTIATE_DYNAMIC_ARRAY_TEMPLATE(element_type)                                                                           \
    typedef struct ing_dynamic_array(element_type) {                                                                                   \
        struct {                                                                                                                       \
            element_type* arr;                                                                                                             \
\
            size_t size,                                                                                                               \
                   capacity;                                                                                                           \
                   \
            void(*element_destructor)(element_type*); \
        } PRIVATE;                                                                                             \
    } ing_dynamic_array(element_type);                                                                                                \
                                                                                                                                       \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_init_with_element_destructor(ing_dynamic_array(element_type)* dynamic_array_ptr, void(*element_destructor)(element_type*)) { \
        memset(dynamic_array_ptr, 0, sizeof(*dynamic_array_ptr));                                                                                                                               \
        dynamic_array_ptr->PRIVATE.element_destructor = element_destructor;                                                                                                                                           \
    }                                                                                                                                  \
    \
    static inline ing_dynamic_array(element_type) ING_PRIVATE_dynamic_array_##element_type##_create_with_element_destructor(void(*element_destructor)(element_type*)) { \
        ing_dynamic_array(element_type) ret;                                                                                           \
        ING_PRIVATE_dynamic_array_##element_type##_init_with_element_destructor(&ret, element_destructor);                             \
                                                                                                                                       \
        return ret;                                                                                                                               \
    }                                                                                                                                  \
          \
    static inline ing_dynamic_array(element_type)* ING_PRIVATE_dynamic_array_##element_type##_create_on_heap_with_element_destructor(void(*element_destructor)(element_type*)) { \
        ing_dynamic_array(element_type)* ret_ptr = malloc(sizeof(ing_dynamic_array(element_type)));                                                                                           \
        ING_PRIVATE_dynamic_array_##element_type##_init_with_element_destructor(ret_ptr, element_destructor);                             \
                                                                                                                                       \
        return ret_ptr;\
    }                                                                                                                                  \
                                                                                                                                       \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_reserve_exact(ing_dynamic_array(element_type)* dynamic_array_ptr, size_t new_capacity) {\
        if(new_capacity > dynamic_array_ptr->PRIVATE.capacity) { \
            void* realloc_result = realloc(dynamic_array_ptr->PRIVATE.arr, sizeof(element_type)*new_capacity);\
            ing_internal_assert(realloc_result);\
            dynamic_array_ptr->PRIVATE.arr = realloc_result;\
            dynamic_array_ptr->PRIVATE.capacity = new_capacity;\
                \
        }\
    }                                                                                                                                  \
                                                                                                                                       \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_reserve(ing_dynamic_array(element_type)* dynamic_array_ptr, size_t new_capacity) {               \
        float old_capacity_f = fmaxf(dynamic_array_ptr->PRIVATE.capacity, 1.f),                                                  \
              new_capacity_target_f = new_capacity;\
        \
        const float growth_constant = 1.5f;\
        \
        float numerator = logf(new_capacity_target_f / old_capacity_f),\
              denominator = logf(growth_constant);\
        float exponent = ceilf(numerator / denominator);\
        \
        float growth_factor = powf(growth_constant, exponent);\
        \
        size_t new_capacity_actual = ceilf(growth_factor * old_capacity_f);\
        \
        ING_PRIVATE_dynamic_array_##element_type##_reserve_exact(dynamic_array_ptr, new_capacity_actual);                                                                                                                                     \
    }                                                                                                                                       \
                                                                                                                                       \
\
    static inline void ING_PRIVATE_dynamic_array_##element_type##_resize(ing_dynamic_array(element_type)* dynamic_array_ptr, size_t new_size) {\
        \
        ING_PRIVATE_dynamic_array_##element_type##_reserve(dynamic_array_ptr, new_size);\
        \
        size_t old_size = dynamic_array_ptr->PRIVATE.size;\
        if(new_size > old_size) {\
            /* zero the new chunk */ \
            memset((char*)(dynamic_array_ptr->PRIVATE.arr)+sizeof(element_type)*old_size, 0, sizeof(element_type)*(new_size-old_size));\
        }                                                                                                                              \
                                                                                                                                       \
        dynamic_array_ptr->PRIVATE.size = new_size;                                                                                                                               \
    }                                                                                                                                       \
                                                                                                                                       \
    static inline element_type* ING_PRIVATE_dynamic_array_##element_type##_back_ptr(ing_dynamic_array(element_type)* dynamic_array_ptr) {             \
        return &dynamic_array_ptr->PRIVATE.arr[dynamic_array_ptr->PRIVATE.size-1];                                     \
    }                                                                                                                                  \
                                                                                                                                       \
    static inline element_type ING_PRIVATE_dynamic_array_##element_type##_back(ing_dynamic_array(element_type)* dynamic_array_ptr) {                  \
        return *ING_PRIVATE_dynamic_array_##element_type##_back_ptr(dynamic_array_ptr);                                                        \
    }                                                                                                                                  \
                                                                                                                                       \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_push_back(ing_dynamic_array(element_type)* dynamic_array_ptr, element_type value) { \
        ING_PRIVATE_dynamic_array_##element_type##_resize(dynamic_array_ptr, dynamic_array_ptr->PRIVATE.size+1);                        \
        *ING_PRIVATE_dynamic_array_##element_type##_back_ptr(dynamic_array_ptr) = value;                                                       \
    }                                                                                                                                  \
    \
    static inline element_type ING_PRIVATE_dynamic_array_##element_type##_pop_back(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        return dynamic_array_ptr->PRIVATE.arr[--dynamic_array_ptr->PRIVATE.size]; \
    }       \
    \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_deinit(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        if(dynamic_array_ptr->PRIVATE.element_destructor) {                                                                            \
            for(size_t i = 0; i < dynamic_array_ptr->PRIVATE.size; ++i) {                                                              \
                dynamic_array_ptr->PRIVATE.element_destructor(&dynamic_array_ptr->PRIVATE.arr[i]);                                                                                                                           \
            }                                                                                                                               \
        }\
    }                                                                                                                                  \
    \
    static inline void ING_PRIVATE_dynamic_array_##element_type##_destroy_heap_allocated(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        ING_PRIVATE_dynamic_array_##element_type##_deinit(dynamic_array_ptr);                                                          \
        free(dynamic_array_ptr);\
    }   \
        \
    static inline size_t ING_PRIVATE_dynamic_array_##element_type##_size(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        return dynamic_array_ptr->PRIVATE.size;\
    }   \
        \
    static inline size_t ING_PRIVATE_dynamic_array_##element_type##_capacity(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        return dynamic_array_ptr->PRIVATE.capacity;\
    }                                                                                                                                  \
                                                                                                                                       \
    static inline element_type* ING_PRIVATE_dynamic_array_##element_type##_data(ing_dynamic_array(element_type)* dynamic_array_ptr) { \
        return dynamic_array_ptr->PRIVATE.arr;\
    }                                                                                                                                  \
                                                                                                                                       \
    static inline element_type* ING_PRIVATE_dynamic_array_##element_type##_at_ptr(ing_dynamic_array(element_type)* dynamic_array_ptr, size_t index) {\
        ing_internal_assert(index < dynamic_array_ptr->PRIVATE.size); \
        return &dynamic_array_ptr->PRIVATE.arr[index];\
    }                                                                                                                                  \
    \
    static inline element_type ING_PRIVATE_dynamic_array_##element_type##_at(ing_dynamic_array(element_type)* dynamic_array_ptr, size_t index) { \
        return *ING_PRIVATE_dynamic_array_##element_type##_at_ptr(dynamic_array_ptr, index);\
    }

#define ing_dynamic_array_create(element_type) \
    (ING_PRIVATE_dynamic_array_##element_type##_create_with_element_destructor(element_type##_destroy))

/// heap allocates an array and "returns" a pointer to it
#define ing_dynamic_array_create_on_heap(element_type)  \
    (ING_PRIVATE_dynamic_array_##element_type##_create_on_heap_with_element_destructor(element_type##_destroy))

/// "returns" a pointer to the dynamic array object
#define ing_dynamic_array_init(element_type, dynamic_array_ptr)              \
    (ING_PRIVATE_dynamic_array_##element_type##_init_with_element_destructor(dynamic_array_ptr, element_type##_destroy))

#define ing_dynamic_array_create_with_element_destructor(element_type, element_destructor) \
    (ING_PRIVATE_dynamic_array_##element_type##_create_with_element_destructor((element_destructor)))

/// heap allocates an array and "returns" a pointer to it
#define ing_dynamic_array_create_on_heap_with_element_destructor(element_type, element_destructor)  \
    (ING_PRIVATE_dynamic_array_##element_type##_create_on_heap_with_element_destructor((element_destructor)))

/// "returns" a pointer to the dynamic array object
#define ing_dynamic_array_init_with_element_destructor(element_type, dynamic_array_ptr, element_destructor)              \
    (ING_PRIVATE_dynamic_array_##element_type##_init_with_element_destructor(dynamic_array_ptr, (element_destructor)))


#define ing_dynamic_array_reserve(element_type, dynamic_array_ptr, size_t_new_capacity)                                                      \
    (ING_PRIVATE_dynamic_array_##element_type##_reserve((dynamic_array_ptr), size_t_new_capacity))

#define ing_dynamic_array_resize(element_type, dynamic_array_ptr, size_t_new_size)                                                        \
    (ING_PRIVATE_dynamic_array_##element_type##_resize((dynamic_array_ptr), size_t_new_size))

#define ing_dynamic_array_resize_no_zero(dynamic_array_ptr, size_t_new_size)                                                    \
    (ING_PRIVATE_dynamic_array_resize_no_zero_type_erased((dynamic_array_ptr), size_t_new_size, sizeof((*(dynamic_array_ptr))->arr)))

#define ing_dynamic_array_size(element_type, dynamic_array_ptr)                \
    (ING_PRIVATE_dynamic_array_##element_type##_size((dynamic_array_ptr)))

#define ing_dynamic_array_capacity(element_type, dynamic_array_ptr)                \
    (ING_PRIVATE_dynamic_array_##element_type##_capacity((dynamic_array_ptr)))

#define ing_dynamic_array_data(element_type, dynamic_array_ptr)                \
    (ING_PRIVATE_dynamic_array_##element_type##_data((dynamic_array_ptr)))

#define ing_dynamic_array_at_ptr(element_type, dynamic_array_ptr, size_t_index)                \
    (ING_PRIVATE_dynamic_array_##element_type##_at_ptr((dynamic_array_ptr), (size_t_index)))

#define ing_dynamic_array_at(element_type, dynamic_array_ptr, size_t_index)                \
    (ING_PRIVATE_dynamic_array_##element_type##_at((dynamic_array_ptr), (size_t_index)))

#define ing_dynamic_array_push_back(element_type, dynamic_array_ptr, value) \
    ING_PRIVATE_dynamic_array_##element_type##_push_back(dynamic_array_ptr, value)

/// "returns" the popped element
#define ing_dynamic_array_pop_back(element_type, dynamic_array_ptr)             \
    (ING_PRIVATE_dynamic_array_##element_type##_pop_back((dynamic_array_ptr)))

/// frees any resources dynamic_array_ptr is holding onto and then calls free(dynamic_array_ptr)
#define ing_dynamic_array_destroy_heap_allocated(element_type, dynamic_array_ptr) \
    (ING_PRIVATE_dynamic_array_##element_type##_destroy_heap_allocated((dynamic_array_ptr)))

/// frees any resources dynamic_array_ptr is holding onto. Doesn't call free on dynamic_array_ptr itself!
#define ing_dynamic_array_deinit(element_type, dynamic_array_ptr) \
    (ING_PRIVATE_dynamic_array_##element_type##_deinit((dynamic_array_ptr)))
