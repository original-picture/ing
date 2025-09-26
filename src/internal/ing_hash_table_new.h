
#pragma once

#include "ing_dynamic_array_new.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct ing_linked_list_node {
    struct ing_linked_list_node* next;
    char value[];
} ing_linked_list_node;

typedef struct {
    ing_linked_list_node* front,
                        * back;

    size_t size;
} ing_linked_list;

struct ing_hash_table;

typedef struct {
    const struct ing_hash_table* source_table;
    size_t bucket_index;
    ing_linked_list_node* node;
} ing_hash_table_iterator;

void* ing_hash_table_iterator_get      (ing_hash_table_iterator* hti);
void  ing_hash_table_iterator_increment(ing_hash_table_iterator* hti);

size_t ing_default_hash (void* value, size_t sizeof_element_type);

bool ing_default_is_equal(void* a, void* b, size_t sizeof_element_type);

typedef struct ing_hash_table {
    ing_dynamic_array array_of_linked_list;

    size_t entries_count;

    size_t (*hash_function)(void* value);
    bool   (*is_equal     )(void* a, void* b);

    void (*element_destructor)(void* element);

    size_t sizeof_element_type,
           default_hash_and_comparison_initial_sequence_length;

    uint8_t index_in_size_table;

} ing_hash_table;

ing_hash_table_iterator ing_hash_table_begin(ing_hash_table* ht);
ing_hash_table_iterator ing_hash_table_end  (ing_hash_table* ht);

void ING_INTERNAL_hash_table_init(ing_hash_table* ht, size_t sizeof_element_type,
                                  size_t (*hash_function)(void* element),
                                  bool   (*is_equal)(void* element_a, void* element_b),
                                  void   (*element_destructor)(void* element),
                                  size_t default_hash_and_comparison_initial_sequence_length);

/*
ing_hash_table ING_INTERNAL_hash_table_create(size_t sizeof_element_type,
                                              void(*hash_function)(void* element),
                                              void(*is_equal)(void* element_a, void* element_b),
                                              void(*element_destructor)(void* element));

ing_hash_table* ING_INTERNAL_hash_table_create_on_heap(size_t sizeof_element_type,
                                                       void(*hash_function)(void* element),
                                                       void(*is_equal)(void* element_a, void* element_b),
                                                       void(*element_destructor)(void* element));
*/

#define ing_hash_table_init(element_type, hash_table_ptr, hash_function, is_equal, element_destructor, size_t_default_hash_initial_sequence_length) \
    (ING_INTERNAL_hash_table_init((hash_table_ptr), sizeof(element_type), (hash_function), (is_equal), (element_destructor), (size_t_default_hash_initial_sequence_length)))

bool ing_hash_table_contains(const ing_hash_table* ht, void* value);

/// returns true if the insertion DID take place (that is, value did not already exist in the table),
/// and false otherwise
bool ing_hash_table_insert  (      ing_hash_table* ht, void* value);

/// an assert will fail if entry doesn't exist
void* ing_hash_table_get          (ing_hash_table* ht, void* value);
void* ing_hash_table_get_or_create(ing_hash_table* ht, void* value);

size_t ing_hash_table_buckets_count(const ing_hash_table* ht);


