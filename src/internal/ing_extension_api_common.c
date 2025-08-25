
#include "ing_extension_api_common.h"

#include "ing_context.h"
#include "ing_core_utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void* ing_allocate_context_data(const char* key, size_t number_of_bytes, void(*destructor)(void*)) {
    ing_internal_assert(current_context->extension_data.arr = realloc(current_context->extension_data.arr, sizeof(extension_datum)*(current_context->extension_data.size)));

    current_context->extension_data.arr[current_context->extension_data.size].key        = key;
    current_context->extension_data.arr[current_context->extension_data.size].destructor = destructor;

    void* ret;
    ing_internal_assert(ret = (current_context->extension_data.arr[current_context->extension_data.size].data = calloc(1, number_of_bytes)));

    ++current_context->extension_data.size;

    return ret;
}

void* ing_get_context_data(const char* key) {
    extension_datum_array* data_array = &current_context->extension_data;
    for(unsigned i = 0; i < data_array->size; ++i) { // this array will be small (< 10 elements), so a linear search will be faster than a hash table
        if(strcmp(key, data_array->arr[i].key) == 0) {
            return data_array->arr[i].data;
        }
    }

    ing_extension_assert(false, "ing_get_context_data invalid key");
    return NULL;
}