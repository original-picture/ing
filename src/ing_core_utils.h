
#pragma once

#include <stddef.h>

/// assert-related stuff
#ifdef ING_DEBUG
#define ING_PRIVATE_STRINGIFY(X) \
    #X

#define ing_internal_assert(condition_expression, /*message*/...)                                                                                \
        {                                                                                                                                        \
            void ing_generic_assert_(_Bool condition, const char* condition_str, const char* message,                                            \
                                     const char* file, int line, const char* function, const char* header_text, const char* footer_text);        \
                                                                                                                                                 \
            ing_generic_assert_(condition_expression, #condition_expression, "" __VA_ARGS__, __FILE__, __LINE__, __func__,                       \
                                "ing internal assertion failed!",                                                                                \
                                "This is the fault of the ing developer(s). If you're just a user of the library, then this isn't your fault.\n" \
                                "Please report this bug here: <github link>)");                                                                  \
        } (void)0
#else
    #define ing_internal_assert(condition_expression, __VA_ARGS_/*message*/) \
        (void)0
#endif

/// dynamic memory stuff
void* ing_allocate(size_t bytes);
void* ing_allocate_and_zero(size_t bytes);

/// asserts if the realloc fails, so you don't have to worry about checking the return value
void* ing_reallocate(void* block, size_t bytes);
void  ing_free(void* block);

/// general memory stuff
void* ing_zero_memory(void* memory, size_t bytes);
void* ing_memcpy(void* dst, void* src, size_t bytes);
void* ing_memcpy_array(void* dst, void* src, size_t elements_count, size_t element_size);

/// copies sizeof(*src) bytes into dst
#define ing_memcpy_src_size(dst, src) \
    ing_memcpy(dst, src, sizeof(*src))

/// copies sizeof(*dst) bytes into dst
#define ing_memcpy_dst_size(dst, src) \
    ing_memcpy(dst, src, sizeof(*dst))