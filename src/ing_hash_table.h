
#pragma once

#include <stdbool.h>

#include "ing_dynamic_array.h"
#include "ing_linked_list.h"


size_t ing_default_hash_int     (int         val);
size_t ing_default_hash_unsigned(unsigned    val);
size_t ing_default_hash_cstring (const char* val);

#define hash_function_type(element_type) \
    hash_function_type_##element_type

#define ing_hash_table(element_type) \
    ing_hash_table_##element_type

#define ING_INSTANTIATE_HASH_TABLE_TEMPLATE(element_type)                                                               \
    typedef struct ing_hash_table(element_type) {                                                                       \
        struct {                                                                                                        \
            ing_dynamic_array_##ing_linked_list_ptr_##element_type arr;                                                     \
            size_t size;                                                                                                \
            float load_factor;                                                                                          \
                                                                                                                        \
            size_t(*hash_function)(element_type);                                                                       \
        } PRIVATE_DO_NOT_ACCESS_SERIOUSLY;                                                                              \
                                                                                                                        \
    } ing_hash_table(element_type);                                                                        \
                                                                                                                        \
    typedef size_t(*hash_function_type_##element_type)(element_type);                                                       \
                                                                                                                        \
                                                                                                                        \
    inline void ing_hash_table_##element_type##_init_with_hash_function(ing_hash_table(element_type)* hash_table_ptr, hash_function_type(element_type) hash_function) { \
        memset(hash_table_ptr, 0, sizeof(*hash_table_ptr));                                                             \
                                                                                                                        \
        hash_table_ptr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.hash_function = hash_function;                                  \
        ing_dynamic_array_resize(&(hash_table_ptr->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.arr), 1); \
    }                                                                                                                   \
                                                                                                                        \
    inline ing_hash_table(element_type) ing_hash_table_##element_type##_create_with_hash_function(hash_function_type(element_type) hash_function) {                   \
        ing_hash_table(element_type) ret;                                                                               \
                                                                                                                        \
        ing_hash_table_##element_type##_init_with_hash_function(&ret, hash_function);                                                                     \
                                                                                                                        \
        return ret;                                                                                                     \
    }                                                                                                                   \
                                                                                                                        \
    inline ing_hash_table(element_type)* ing_hash_table_##element_type##_create_on_heap_with_hash_function(hash_function_type(element_type) hash_function) {          \
        ing_hash_table(element_type)* ret = malloc(sizeof(*ret));                                                       \
                                                                                                                        \
        ing_hash_table_##element_type##_init_with_hash_function(ret, hash_function);                                    \
                                                                                                                        \
        return ret;                                                                                                     \
    }                                                                                                                   \
                                                                                                                        \
    inline void ing_hash_table_##element_type##_insert(ing_hash_table(element_type)* hash_table, element_type value) {             \
                                                                                                                        \
    }                                                                                                                                   \
                                                                                                                    \
    inline bool ing_hash_table_##element_type##_contains(ing_hash_table(element_type)* hash_table, element_type value) {             \
        size_t hash = hash_table->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.hash_function(value);                                 \
        size_t bucket_index = hash % ing_dynamic_array_size(&hash_table->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.arr);          \
                                                                                                                        \
        ing_linked_list(element_type)* node = hash_table->PRIVATE_DO_NOT_ACCESS_SERIOUSLY.arr.arr[bucket_index];          \
        while(node) {                                                                                                   \
            if(value = node->value) {                                                                                   \
                return true;                                                                                                            \
            }                                                                                                           \
                                                                                                                        \
            node = node->next; \
        }                                                                                                               \
                                                                                                                        \
        return false;\
    }

#define ing_hash_table_init_with_hash_function(element_type, hash_table_ptr, hash_function)      \
    (ing_hash_table_##element_type##_init_with_hash_function((hash_table_ptr), (hash_function)))

#define ing_hash_table_create_with_hash_function(element_type, hash_function)    \
    (ing_hash_table_##element_type##_create_with_hash_function((hash_function)))

#define ing_hash_table_create_on_heap_with_hash_function(element_type, hash_function)    \
    (ing_hash_table_##element_type##_create_on_heap_with_hash_function((hash_function)))

#define ing_hash_table_insert(element_type, hash_table_ptr, value) \
    (ing_hash_table_##element_type##_insert((hash_table_ptr), (value)))


#define ing_hash_table_init(element_type, hash_table_ptr) \
    (ing_hash_table_init_with_hash_function(element_type, hash_table_ptr, (ing_default_hash_##element_type)))

#define ing_hash_table_create(element_type) \
    (ing_hash_table_create_with_hash_function(element_type, (ing_default_hash_##element_type)))

#define ing_hash_table_create_on_heap(element_type) \
    ing_hash_table_create_on_heap_with_hash_function(element_type, (ing_default_hash_##element_type))

#define ing_hash_table_contains(element_type, hash_table_ptr, value) \
    ing_hash_table_##element_type##_contains((hash_table_ptr), (value))

/// the implementation of hash table uses dynamic_array(linked_list(element_type))
/// this macro will instantiate linked_list(element_type) and dynamic_array(linked_list(element_type)) in addition to hash_table(element_type)
/// if these types have already been instantiated and included, then use ING_INSTANTIATE_HASH_TABLE_TEMPLATE instead
/// you'll also have to manually add the typdef
///     typedef ing_linked_list_##element_type* linked_list_ptr##element_type;
/// because an actual star will mess up macro concatenation
#define ING_INSTANTIATE_HASH_TABLE_TEMPLATE_AND_DEPENDENCY_TEMPLATES(element_type) \
    ING_INSTANTIATE_LINKED_LIST_TEMPLATE(element_type);                            \
    typedef ing_linked_list_##element_type* ing_linked_list_ptr_##element_type;        \
    ING_INSTANTIATE_DYNAMIC_ARRAY_TEMPLATE(ing_linked_list_ptr_##element_type)         \
                                                                                   \
    ING_INSTANTIATE_HASH_TABLE_TEMPLATE(element_type)

