
#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct linked_list_node {
    struct linked_list_node* next;
    char data[];
} linked_list_node;

typedef struct {
    linked_list_node* front;
    size_t size;

    size_t sizeof_element_type;
} linked_list;


typedef struct {
    size_t bucket_index;
    linked_list_node* node;
} hash_table_iterator;

void* hash_table_iterator_get(hash_table_iterator* hti);
void hash_table_iterator_increment(hash_table_iterator* hti);


typedef struct {
    linked_list* array;

    size_t entries_count,
           buckets_count;

    size_t sizeof_element_type;
} hash_table;

hash_table_iterator hash_table_begin(hash_table* ht);
hash_table_iterator hash_table_end(hash_table* ht);

void hash_table_init(hash_table* ht, size_t sizeof_element_type,
                     void(*hash_function)(void* element, size_t sizeof_element_type),
                     void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                     void(*element_destructor)(void* element, size_t sizeof_element_type));

void hash_table_init_default(hash_table* ht, size_t sizeof_element_type);

hash_table  hash_table_create(size_t sizeof_element_type,
                              void(*hash_function)(void* element, size_t sizeof_element_type),
                              void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                              void(*element_destructor)(void* element, size_t sizeof_element_type));

hash_table* hash_table_create_on_heap(size_t sizeof_element_type,
                                      void(*hash_function)(void* element, size_t sizeof_element_type),
                                      void(*is_equal)(void* element_a, void* element_b, size_t sizeof_element_type),
                                      void(*element_destructor)(void* element, size_t sizeof_element_type));

bool hash_table_contains(const hash_table* ht, void* value);
bool hash_table_insert(hash_table* ht, void* value);

/// creates the entry if it doesn't exist
void* hash_table_at(hash_table* ht, void* value);