
#include "ing_dynamic_array.h"

#include "ing_core_utils.h"

typedef struct type_erased_array {
    void* arr;

    struct {
        size_t size,
               capacity;

    } PRIVATE;
} type_erased_array;


void ING_PRIVATE_dynamic_array_reserve_type_erased(void* dynamic_array_ptr, size_t new_capacity, size_t size_of_element_type) {
    type_erased_array erased; // woah like the anime
    memcpy(&erased, dynamic_array_ptr, sizeof(erased)); // type erasure via memcpy to prevent strict aliasing nasal demons
                                                     // any sane compiler will optimize out the actual copying
    if(new_capacity > erased.PRIVATE.capacity) { // I get to access private data cuz I wrote the library
        void* realloc_result = realloc(erased.arr, size_of_element_type*new_capacity);
        ing_internal_assert(realloc_result);
        erased.arr = realloc_result;

        erased.PRIVATE.capacity = new_capacity;

        memcpy(dynamic_array_ptr, &erased, sizeof(erased)); // and now update the real object with our changes
    }
}

void ING_PRIVATE_dynamic_array_resize_type_erased(void* dynamic_array_ptr, size_t new_size, size_t size_of_element_type) {
    type_erased_array erased; // woah like the anime
    memcpy(&erased, dynamic_array_ptr, sizeof(erased)); // type erasure via memcpy to prevent strict aliasing nasal demons
                                                        // any sane compiler will optimize out the actual copying

    ING_PRIVATE_dynamic_array_reserve_type_erased(&erased, new_size, size_of_element_type);

    size_t old_size = erased.PRIVATE.size;
    if(new_size > old_size) {


        // zero the new chunk
        memset((char*)(erased.arr)+size_of_element_type*old_size, 0, size_of_element_type*(new_size-old_size));
    }

    erased.PRIVATE.size = new_size;
    memcpy(dynamic_array_ptr, &erased, sizeof(erased)); // and now update the real object with our changes
}

void ING_PRIVATE_dynamic_array_resize_no_zero_type_erased(void* dynamic_array_ptr, size_t new_size, size_t size_of_element_type) {
    type_erased_array erased; // woah like the anime
    memcpy(&erased, dynamic_array_ptr, sizeof(erased)); // type erasure via memcpy to prevent strict aliasing nasal demons
                                                        // any sane compiler will optimize out the actual copying

    ING_PRIVATE_dynamic_array_reserve_type_erased(&erased, new_size, size_of_element_type);

    erased.PRIVATE.size = new_size;
    memcpy(dynamic_array_ptr, &erased, sizeof(erased)); // and now update the real object with our changes
}

void ING_PRIVATE_dynamic_array_free(void* dynamic_array_ptr) {
    type_erased_array erased; // woah like the anime
    memcpy(&erased, dynamic_array_ptr, sizeof(erased)); // type erasure via memcpy to prevent strict aliasing nasal demons
                                                        // any sane compiler will optimize out the actual copying

    free(erased.arr);
    free(dynamic_array_ptr);
}