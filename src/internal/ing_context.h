#pragma once

#include <stdbool.h>
#include <stddef.h>

// this is a C99 library, so I can't use _Thread_local from C11
// also I'd need to check for C23 too because _Thread_local was replaced with thread_local in C23
// and I don't feel like doing all that
#ifdef _MSC
    #define ING_THREADLOCAL __declspec(thread)
#else
    #define ING_THREADLOCAL __thread // it's the same on gcc and clang
#endif

typedef struct {
    const char* key;
    void* data;
    void(*destructor)(void*);
} extension_datum;

typedef struct {
    extension_datum* arr;
    size_t size;
} extension_datum_array;

typedef struct {
    bool should_quit;
    extension_datum_array extension_data;
} ing_context;

extern ING_THREADLOCAL ing_context* current_context;

ing_context* init_context();

void make_context_current(ing_context* context);

ing_context* init_context_and_make_current(void(*backend_specific_init_callback)());

// current_context is zeroed when it's initialized
void conditional_init_current_context(void(*backend_specific_init_callback)());

