#pragma once

#include <stddef.h>

/// allocates number_of_bytes of storage and returns
unsigned ing_allocate_per_context_data(size_t number_of_bytes);


void* ing_get_per_context_data(unsigned handle);