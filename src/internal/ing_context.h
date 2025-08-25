#pragma once

#include <stdbool.h>

// this is a C99 library, so I can't use _Thread_local from C11
// also I'd need to check for C23 too because _Thread_local was replaced with thread_local in C23
// and I don't feel like doing all that
#ifdef _MSC
    #define ING_THREADLOCAL __declspec(thread)
#else
    #define ING_THREADLOCAL __thread // it's the same on gcc and clang
#endif

typedef struct ing_context {
    bool should_quit;
} ing_context;

extern ING_THREADLOCAL ing_context* current_context;

// current_context is zeroed when it's initialized
void conditional_init_context(void(*backend_specific_init_callback)());

