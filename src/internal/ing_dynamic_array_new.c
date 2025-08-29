
#include "ing_dynamic_array_new.h"

#include "ing_core_utils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

void INTERNAL_dynamic_array_init(dynamic_array* da, size_t sizeof_element_type,
                        void(*element_destructor)(void* element)
                        #ifdef ING_DEBUG
                            , const char* element_typename
                        #endif
                        ) {

    memset(da, 0, sizeof(dynamic_array));
    da->element_destructor = element_destructor;

    #ifdef ING_DEBUG
        da->element_typename = element_typename;
    #endif
}

dynamic_array* dynamic_array_create_on_heap(size_t sizeof_element_type,
                                            void(*element_destructor)(void* element)
                                            #ifdef ING_DEBUG
                                                , const char* element_typename
                                            #endif
                                            ) {

    dynamic_array* ret = malloc(sizeof(dynamic_array));

    INTERNAL_dynamic_array_init(ret, sizeof_element_type, element_destructor
    #ifdef ING_DEBUG
        , element_typename
    #endif
    );

    return ret;
}

void dynamic_array_reserve(dynamic_array* da, size_t new_capacity) {
    if(new_capacity > da->capacity) {
        void* data = realloc(da->data, new_capacity*da->sizeof_element_type);
        ing_internal_assert(data);
        da->data = data;

        da->capacity = new_capacity;
    }
}

void dynamic_array_resize(dynamic_array* da, size_t new_size) {
    dynamic_array_reserve(da, new_size);

    if(new_size > da->size) {
        // zero the new elements
        memset(da->data+da->sizeof_element_type*da->size, 0, da->sizeof_element_type*(new_size-da->size));

        da->size = new_size;
    }

    da->size = new_size;
}

void* INTERNAL_dynamic_array_at(dynamic_array* da, size_t index
                                #ifdef ING_DEBUG
                                    , const char* element_typename
                                #endif
                                ) {

    ing_internal_assert(strcmp(element_typename, da->element_typename) == 0);

    return da->data+index*da->sizeof_element_type;
}


void dynamic_array_resize_geometric_(dynamic_array* da, size_t new_size) {
    if(new_size > da->capacity) {
        float old_capacity_f = fmaxf(da->capacity, 1.f),
                new_capacity_target_f = new_size;

        const float growth_constant = 1.5f;

        float numerator = logf(new_capacity_target_f / old_capacity_f),
              denominator = logf(growth_constant);

        float exponent = ceilf(numerator / denominator);
        float growth_factor = powf(growth_constant, exponent);

        size_t new_capacity_actual = ceilf(growth_factor * old_capacity_f);

        dynamic_array_reserve(da, new_capacity_actual);
    }
    else if(new_size < da->size) {

    }
}

void INTERNAL_dynamic_array_push_back(dynamic_array* da, void* value
                                      #ifdef ING_DEBUG
                                          , const char* element_typename
                                      #endif
                                      ) {

    ing_internal_assert(strcmp(element_typename, da->element_typename) == 0);

    dynamic_array_resize_geometric_(da, da->size+1);

    memcpy(INTERNAL_dynamic_array_at(da, da->size-1
                                     #ifdef ING_DEBUG
                                         , element_typename
                                     #endif
                                     ),
           value,
           da->sizeof_element_type);
}