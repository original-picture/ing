
#pragma once

#include <stdlib.h>
#include <string.h>


/// returns dynamic_array_ptr
void ING_PRIVATE_dynamic_array_reserve_type_erased(void* dynamic_array_ptr, size_t new_capacity, size_t size_of_element_type);

void ING_PRIVATE_dynamic_array_resize_type_erased(void* dynamic_array_ptr, size_t new_size, size_t size_of_element_type);

/// same as resize, but it doesn't zero the new part of the array (if new_size is greater than the old size of the array)
void ING_PRIVATE_dynamic_array_resize_no_zero_type_erased(void* dynamic_array_ptr, size_t new_size, size_t size_of_element_type);

void ING_PRIVATE_dynamic_array_free(void* dynamic_array_ptr);

#define ing_dynamic_array(element_type, /*hash_function*/...) \
    ing_dynamic_array_##element_type

#define ING_INSTANTIATE_DYNAMIC_ARRAY_TEMPLATE(element_type)                                                                           \
    typedef struct ing_dynamic_array(element_type) {                                                                                   \
        element_type* arr;                                                                                                             \
                                                                                                                                       \
        struct {                                                                                                                       \
            size_t size,                                                                                                               \
                   capacity;                                                                                                           \
                                                                                                                                       \
        } PRIVATE_DO_NOT_ACCESS_SERIOUSLY;                                                                                             \
    } ing_dynamic_array_##element_type;                                                                                                \
                                                                                                                                       \
                                                                                                                                       \
    inline element_type* ing_dynamic_array_##element_type##_back_ptr(ing_dynamic_array(element_type)* dynamic_array_ptr) {             \
        return &dynamic_array_ptr->arr[dynamic_array_ptr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size-1];                                     \
    }                                                                                                                                  \
                                                                                                                                       \
    inline element_type ing_dynamic_array_##element_type##_back(ing_dynamic_array(element_type)* dynamic_array_ptr) {                  \
        return *ing_dynamic_array_##element_type##_back_ptr(dynamic_array_ptr);                                                        \
    }                                                                                                                                  \
                                                                                                                                       \
    inline void ing_dynamic_array_##element_type##_push_back(ing_dynamic_array(element_type)* dynamic_array_ptr, element_type value) { \
        ing_dynamic_array_resize(dynamic_array_ptr, dynamic_array_ptr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size+1);                        \
        *ing_dynamic_array_##element_type##_back_ptr(dynamic_array_ptr) = value;                                                       \
    }


#define ing_dynamic_array_create(element_type) \
    ((ing_dynamic_array(element_type)){})

/// heap allocates an array and "returns" a pointer to it
#define ing_dynamic_array_create_on_heap(element_type)  \
    (calloc(1,sizeof(ing_dynamic_array(element_type))))

/// "returns" a pointer to the dynamic array object
#define ing_dynamic_array_init(dynamic_array_ptr)              \
    (memset(dynamic_array_ptr, 0, sizeof(*dynamic_array_ptr)))

#define ing_dynamic_array_reserve(dynamic_array_ptr, size_t_new_capacity)                                                      \
    (ING_PRIVATE_dynamic_array_reserve_type_erased((dynamic_array_ptr), size_t_new_capacity, sizeof(*dynamic_array_ptr->arr)))

#define ing_dynamic_array_resize(dynamic_array_ptr, size_t_new_size)                                                        \
    ((ING_PRIVATE_dynamic_array_resize_type_erased((dynamic_array_ptr), size_t_new_size, sizeof(*((dynamic_array_ptr)->arr)))))

#define ing_dynamic_array_resize_no_zero(dynamic_array_ptr, size_t_new_size)                                                    \
    (ING_PRIVATE_dynamic_array_resize_no_zero_type_erased((dynamic_array_ptr), size_t_new_size, sizeof((*(dynamic_array_ptr))->arr)))

#define ing_dynamic_array_size(dynamic_array_ptr)                \
    ((dynamic_array_ptr)->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size);

#define ing_dynamic_array_capacity(dynamic_array_ptr)                \
    ((dynamic_array_ptr)->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.capacity);

#define ing_dynamic_array_push_back(element_type, dynamic_array_ptr, value) \
    ing_dynamic_array_##element_type##_push_back(dynamic_array_ptr, value)

#define ing_dynamic_array_pop_back(dynamic_array_ptr)             \
    (--(dynamic_array_ptr)->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.size)

/// frees any resources dynamic_array_ptr is holding onto and then calls free(dynamic_array_ptr)
#define ing_dynamic_array_destroy_heap_allocated(dynamic_array_ptr) \
    (ING_PRIVATE_dynamic_array_free(dynamic_array_ptr))

/// frees any resources dynamic_array_ptr is holding onto. Doesn't call free on dynamic_array_ptr itself!
#define ing_dynamic_array_deinit(dynamic_array_ptr) \
    (free((dynamic_array_ptr)->arr))
