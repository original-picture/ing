
#pragma once

#include "ing_context_data_common.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct {
    HMODULE instance;
    HWND* windows; // array of all top-level windows we've created. We need to iterate over them and call IsDialogMessage

} win32_context_data;