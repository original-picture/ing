
#pragma once


#define ing_linked_list(element_type) \
    ing_linked_list_##element_type

#define ING_INSTANTIATE_LINKED_LIST_TEMPLATE(element_type) \
    typedef struct ing_linked_list(element_type) {         \
        element_type value;                                \
        struct ing_linked_list(element_type)* next;        \
    } ing_linked_list(element_type)

