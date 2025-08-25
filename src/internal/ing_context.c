
#include "ing_context.h"

#include "ing_core_utils.h"

#include <stdlib.h>

ING_THREADLOCAL ing_context* current_context;

ing_context* init_context() {
    ing_context* ret = calloc(1, sizeof(ing_context));
    ing_internal_assert(ret, "calloc failed to allocate memory for context");

    return ret;
}

void make_context_current(ing_context* context) {
    current_context = context;
}

ing_context* init_context_and_make_current(void(*backend_specific_init_callback)()) {
    ing_context* ret = init_context();
    make_context_current(ret);

    if(backend_specific_init_callback) {
        backend_specific_init_callback();
    }

    return ret;
}

void conditional_init_current_context(void(*backend_specific_init_callback)()) {
    if(!current_context) {
        init_context_and_make_current(backend_specific_init_callback);
    }
}

// implementing this here and not in the extension api because quit doesn't need to be extended at all
void ing_quit_at_end_of_frame() {
    current_context->should_quit = true;
}