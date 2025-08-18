
#include "ing_test_hash_table.h"

#include "ing_hash_table.h"

#include "ing_testing_assert.h"

//ING_INSTANTIATE_HASH_TABLE_TEMPLATE_AND_DEPENDENCY_TEMPLATES(unsigned);

static size_t alternate_hash_function(unsigned val) {
    return 0;
}

static void test_create() {
//   {
//       {
//           ing_hash_table(unsigned) ht = ing_hash_table_create(unsigned);

//           ing_testing_assert(ht.PRIVATE.size == 0);
//           ing_testing_assert(ht.PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht.PRIVATE.hash_function == ing_default_hash_unsigned);
//       }

//       {
//           ing_hash_table(unsigned)* ht = ing_hash_table_create_on_heap(unsigned);

//           ing_testing_assert(ht->PRIVATE.size == 0);
//           ing_testing_assert(ht->PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht->PRIVATE.hash_function == ing_default_hash_unsigned);
//       }

//       {
//           ing_hash_table(unsigned) ht;

//           ing_hash_table_init(unsigned, &ht);

//           ing_testing_assert(ht.PRIVATE.size == 0);
//           ing_testing_assert(ht.PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht.PRIVATE.hash_function == ing_default_hash_unsigned);
//       }
//   }

//   {
//       {
//           ing_hash_table(unsigned) ht = ing_hash_table_create_with_hash_function(unsigned, alternate_hash_function);

//           ing_testing_assert(ht.PRIVATE.size == 0);
//           ing_testing_assert(ht.PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht.PRIVATE.hash_function == alternate_hash_function);
//       }

//       {
//           ing_hash_table(unsigned)* ht = ing_hash_table_create_on_heap_with_hash_function(unsigned, alternate_hash_function);

//           ing_testing_assert(ht->PRIVATE.size == 0);
//           ing_testing_assert(ht->PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht->PRIVATE.hash_function == alternate_hash_function);
//       }

//       {
//           ing_hash_table(unsigned) ht;

//           ing_hash_table_init_with_hash_function(unsigned, &ht, alternate_hash_function);

//           ing_testing_assert(ht.PRIVATE.size == 0);
//           ing_testing_assert(ht.PRIVATE.load_factor == 0.f);

//           ing_testing_assert(ht.PRIVATE.hash_function == alternate_hash_function);

//           ing_hash_table_contains(unsigned, &ht, 12);

//          // ing_
//       }
//   }
}

static void test_insert() {
    {
    //    ing_hash_table(unsigned)* ht = ing_hash_table_create_on_heap(unsigned);
//
    //    ing_hash_table_insert(unsigned, ht, 32);
    }
}

void test_hash_table() {
    test_create();
    test_insert();
}