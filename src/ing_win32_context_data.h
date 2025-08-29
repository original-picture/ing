
#pragma once

#include "ing_context_data_common.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "internal/ing_dynamic_array_new.h"

typedef struct {
    HMODULE instance;
    dynamic_array top_level_windows; // array of all top-level windows we've created. We need to iterate over them and call IsDialogMessage

} win32_context_data;