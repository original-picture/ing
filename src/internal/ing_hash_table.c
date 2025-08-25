
#include <string.h>
#include <stdbool.h>

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

/// returns an incorrect result for number==0 and number==1!
bool ING_PRIVATE_is_prime(size_t number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0) { return false; }
    }
    return true;
}

size_t ING_PRIVATE_next_prime_after(size_t number) {
    if(number % 2 != 0) {
        ++number;
    }

    while(!ING_PRIVATE_is_prime(number)) {
        number += 2;
    }
    return number;
}