#pragma once

#include <stddef.h>

#ifdef __cplusplus
    extern "C" {
#endif

    #ifdef ING_DEBUG
        #define ing_extension_assert(condition_expression, /*message*/...)                                                                           \
            {                                                                                                                                        \
                void ing_generic_assert_(_Bool condition, const char* condition_str, const char* message,                                            \
                                         const char* file, int line, const char* function, const char* header_text, const char* footer_text);        \
                                                                                                                                                     \
                ing_generic_assert_(condition_expression, #condition_expression, "" __VA_ARGS__, __FILE__, __LINE__, __func__,                       \
                                    "ing extension assertion failed!",                                                                               \
                                    "This is the fault of the extension developer(s). If you're just a user of the library, then this isn't your fault.\n");                                                                  \
            } (void)0
    #else
        #define ing_extension_assert(condition_expression, __VA_ARGS_/*message*/) \
            condition_expression
    #endif

    /// allocates number_of_bytes of storage in the current context and returns a pointer to it
    /// an assert will fail if key already exists
    /// destructor can be NULL, in which case it will do nothing
    void* ing_allocate_context_data(const char* key, size_t number_of_bytes, void(*destructor)(void*));

    /// retrieves the pointer associated with key
    /// an assert will fail if key doesn't exist
    void* ing_get_context_data(const char* key);

#ifdef __cplusplus
    };
#endif