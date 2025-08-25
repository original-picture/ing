#pragma once

#include <stdbool.h>

bool ing_next_frame_internal(void(*backend_specific_init_callback)(), void(*backend_specific_per_frame_callback)());