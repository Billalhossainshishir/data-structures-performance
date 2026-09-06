#include <stdio.h>

#include "array_m2m_db.h"
#include "avl_m2m_db.h"
#include "hash_m2m_db.h"

static void demo_array(void) {
    ArrayM2MDB db;
    array_db_init(&db);
    array_insert_customer(&db, "C001");
    array_insert_restaurant(&db, "R001");
    printf("Array prototype: %s\n", array_place_order(&db, "C001", "R001") ? "OK" : "FAILED");
    array_db_destroy(&db);
}

static void demo_avl(void) {
    AVLM2MDB db;
    avl_db_init(&db);
    avl_insert_customer(&db, "C001");
    avl_insert_restaurant(&db, "R001");
    printf("AVL prototype: %s\n", avl_place_order(&db, "C001", "R001") ? "OK" : "FAILED");
    avl_db_destroy(&db);
}

static void demo_hash(void) {
    HashM2MDB db;
    hash_db_init(&db);
    hash_insert_customer(&db, "C001");
    hash_insert_restaurant(&db, "R001");
    printf("Hash prototype: %s\n", hash_place_order(&db, "C001", "R001") ? "OK" : "FAILED");
    hash_db_destroy(&db);
}

int main(void) {
    puts("Data Structures Performance Demo");
    puts("================================");
    demo_array();
    demo_avl();
    demo_hash();
    return 0;
}
