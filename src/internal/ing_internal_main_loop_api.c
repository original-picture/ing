
#include "ing_internal_main_loop_api.h"

#include "ing_context.h"

bool ing_next_frame_internal(void(*backend_specific_init_callback)(), void(*backend_specific_per_frame_callback)()) {
    conditional_init_context();

    backend_specific_per_frame_callback();

    if(current_context->should_quit) {
        return false;
    }
    return true;
}
