
#include "ing_dynamic_array_new.h"

#include "ing_core_utils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

void ING_INTERNAL_dynamic_array_init(ing_dynamic_array* da, size_t sizeof_element_type,
                        void(*element_destructor)(void* element)) {

    memset(da, 0, sizeof(ing_dynamic_array));
    da->sizeof_element_type = sizeof_element_type;
    da->element_destructor = element_destructor;
}

ing_dynamic_array* ING_INTERNAL_dynamic_array_create_on_heap(size_t sizeof_element_type,
                                            void(*element_destructor)(void* element)) {

    ing_dynamic_array* ret = malloc(sizeof(ing_dynamic_array));

    ING_INTERNAL_dynamic_array_init(ret, sizeof_element_type, element_destructor);

    return ret;
}

void ing_dynamic_array_reserve(ing_dynamic_array* da, size_t new_capacity) {
    if(new_capacity > da->capacity) {
        void* data = realloc(da->data, new_capacity*da->sizeof_element_type);
        ing_internal_assert(data);
        da->data = data;

        da->capacity = new_capacity;
    }
}

void ing_dynamic_array_resize(ing_dynamic_array* da, size_t new_size) {
    ing_dynamic_array_reserve(da, new_size);

    if(new_size > da->size) {
        // zero the new elements
        memset(da->data+da->sizeof_element_type*da->size, 0, da->sizeof_element_type*(new_size-da->size));

        da->size = new_size;
    }

    da->size = new_size;
}

void* ing_dynamic_array_at_ptr(ing_dynamic_array* da, size_t index) {
    ing_internal_assert(index < da->size);
    return da->data+da->sizeof_element_type*index;
}

void* ing_dynamic_array_at_as_void_ptr(ing_dynamic_array* da, size_t index) {
            // this is not a strict aliasing violation (I think)
    return *(void**)(da->data+index*da->sizeof_element_type);
}

void ing_dynamic_array_resize_geometric_(ing_dynamic_array* da, size_t new_size) {
    if(new_size > da->capacity) {
        float old_capacity_f = fmaxf(da->capacity, 1.f),
                new_capacity_target_f = new_size;

        const float growth_constant = 1.5f;

        float numerator = logf(new_capacity_target_f / old_capacity_f),
              denominator = logf(growth_constant);

        float exponent = ceilf(numerator / denominator);
        float growth_factor = powf(growth_constant, exponent);

        size_t new_capacity_actual = ceilf(growth_factor * old_capacity_f);

        ing_dynamic_array_reserve(da, new_capacity_actual);
    }

    ing_dynamic_array_resize(da, new_size);
}

void ing_dynamic_array_push_back(ing_dynamic_array* da, void* value) {
    ing_dynamic_array_resize_geometric_(da, da->size+1);

    memcpy(ing_dynamic_array_at_ptr(da, da->size-1),
           value,
           da->sizeof_element_type);
}

void ing_dynamic_array_destroy(ing_dynamic_array* da) {
    if(da->element_destructor) { // if they didn't, try to use the dynamic array's element destructor
        for(size_t i = 0; i < da->size; ++i) {
            da->element_destructor(da->data+i*da->sizeof_element_type);
        }
    }

    free(da->data);
}