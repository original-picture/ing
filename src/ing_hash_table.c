
#include <string.h>

#define GENERATE_DEFAULT_VALUE_HASH_FUNCTION_DEFINITION(TYPE) \
size_t ing_default_hash_##TYPE(TYPE val) {                       \
    size_t ret = 0;                                           \
    memcpy(&ret, &val, sizeof(val));                          \
    return ret;                                               \
}


GENERATE_DEFAULT_VALUE_HASH_FUNCTION_DEFINITION(int);
GENERATE_DEFAULT_VALUE_HASH_FUNCTION_DEFINITION(unsigned);

size_t ing_default_hash_cstring(const char* val) {
    /// source for this implementation: http://www.cse.yorku.ca/~oz/hash.html
    size_t hash = 5381;

    char c;
    while(c = *val++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
    /// /source
}
