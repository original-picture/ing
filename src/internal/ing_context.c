
#include "ing_context.h"

#include "ing_core_utils.h"

#include <stdlib.h>

ING_THREADLOCAL ing_context* current_context;

void conditional_init_context(void(*backend_specific_init_callback)()) {
    if(!current_context) {
        current_context = calloc(1, sizeof(ing_context));

        ing_internal_assert(current_context, "calloc failed to allocate memory for context");

        backend_specific_init_callback();
    }
}