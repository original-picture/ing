
#include "ing_core_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// different kinds of asserts use this generic template to generate error messages with different headers and footers
/// so for example, an internal assert will have a footer that says something to the effect of "this isn't your (the user's) fault",
/// whereas a user error assert will have a footer that tells that user that they messed up
void ing_generic_assert_(bool condition, const char* condition_str, const char* message,
                         const char* file, int line, const char* function, const char* header_text, const char* footer_text) {
    if(!condition) {
        fprintf(stderr, "%s\n\n"

                        "   in function\n"
                        "       %s\n"
                        "   In file\n"
                        "       %s:%i\n"
                        "   the condition:\n"
                        "       %s\n"
                        "   evaluated to false.\n\n"
                        "   Message:\n"
                        "       %s\n\n"

                        "%s\n",

                        header_text,
                        function,
                        file,
                        line,
                        condition_str,
                        (*message ? message : "(no additional information given)"),
                      // ^ if string is not empty

                        footer_text);

        abort();
    }
}

void ing_internal_assert_(bool condition, const char* condition_str, const char* message,
                          const char* file, int line, const char* function) {

    ing_generic_assert_(condition, condition_str, message,
                        file, line, function,

                        "ing internal assertion failed!\n\n",

                        "This is the fault of the ing developer(s). If you're just a user of the library, then this isn't your fault.\n"
                        "Please report this bug here: <github link>)");
}

void* ing_allocate(size_t bytes) {
    void* ret = malloc(bytes);
    ing_internal_assert(ret);

    return ret;
}

void* ing_allocate_and_zero(size_t bytes) {
    void* ret = calloc(1, bytes);
    ing_internal_assert(ret);

    return ret;
}

void* ing_reallocate(void* block, size_t bytes) {
    void* ret = realloc(block, bytes);
    ing_internal_assert(ret);

    return ret;
}

void ing_free(void* block) {
    ing_internal_assert(block);
    free(block);
}

void* ing_zero_memory(void* memory, size_t bytes) {
    return memset(memory, 0, bytes);
}

void* ing_memcpy(void* dst, void* src, size_t bytes) {
    return memcpy(dst, src, bytes);
}

void* ing_memcpy_array(void* dst, void* src, size_t elements_count, size_t element_size) {
    return ing_memcpy(dst, src, elements_count*element_size);
}