
#include "ing_main_loop_extension_api.h"

#include "ing_context.h"

#include <stdlib.h>

// TODO: rename
bool ing_next_frame_internal(void(*backend_specific_init_callback)(),
                             void(*backend_specific_per_frame_callback)(),
                             void(*backend_specific_deinit_callback)()) {
    conditional_init_current_context(backend_specific_init_callback);

    backend_specific_per_frame_callback();

    if(backend_specific_deinit_callback) {
        backend_specific_deinit_callback();
    }

    if(current_context->should_quit) {
        for(unsigned i = 0; i < current_context->extension_data.size; ++i) {
            extension_datum* datum = current_context->extension_data.arr+i;

            if(datum->destructor) {
                datum->destructor(datum->data);
            }

            free(datum->data);
        }

        free(current_context->extension_data.arr);

        return false;
    }
    return true;
}
