#pragma once

#include "ing_extension_api_common.h"

#include <stdbool.h>

#ifdef __cplusplus
    extern "C" {
#endif

    /// backend_specific_deinit_callback is called before any of the destructors provided in ing_allocate_context_data
    bool ing_next_frame_internal(void(*backend_specific_init_callback)(),
                                 void(*backend_specific_per_frame_callback)(),
                                 void(*backend_specific_deinit_callback)());

#ifdef __cplusplus
    };
#endif