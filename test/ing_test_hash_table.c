
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

    ing_hash_table_init(int, &ht, NULL, NULL, NULL);

    ing_testing_assert(ht.buckets_count == 0);
    ing_testing_assert(ht.entries_count == 0);
}

static void test_insert_contains() {
    ing_hash_table ht;

    ing_hash_table_init(int, &ht, NULL, NULL, NULL, 0);
}

static void test_insert() {
    {
   //ing_hash_table(unsigned)* ht = ing_hash_table_create_on_heap(unsigned);

  // ing_hash_table_insert(unsigned, ht, 32);
    }
}

void test_hash_table() {
    test_create();
    test_insert();
    test_insert_contains();
}