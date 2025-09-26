
#include "ing_test_hash_table.h"

#include "ing_hash_table_new.h"

#include "ing_testing_assert.h"
 // TODO
//ING_INSTANTIATE_HASH_TABLE_TEMPLATE_AND_DEPENDENCY_TEMPLATES(unsigned);

static size_t alternate_hash_function(unsigned val) {
    return 0;
}

static void test_create() {
    //hash_table

    ing_hash_table ht;

    ing_hash_table_init(int, &ht, NULL, NULL, NULL, 0);

    ing_testing_assert(ht.array_of_linked_list.size == 0);
    ing_testing_assert(ht.entries_count == 0);
}

static void test_insert_contains() {
    ing_hash_table ht;

    ing_hash_table_init(int, &ht, NULL, NULL, NULL, 0);
}

static void test_insert() {
    {
    ing_hash_table ht;
    ing_hash_table_init(unsigned, &ht, NULL, NULL, NULL, 0);

    unsigned u = 32;
    ing_hash_table_insert(&ht, &u);
    ing_testing_assert(ing_hash_table_contains(&ht, &u));
    }
}

void test_hash_table() {
    test_create();
    test_insert();
    test_insert_contains();
}