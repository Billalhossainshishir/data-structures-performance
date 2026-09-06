#ifndef HASH_M2M_DB_H
#define HASH_M2M_DB_H

#include "assoc_list.h"

#define HASH_TABLE_SIZE 101
#define HASH_ID_SIZE 20

typedef struct hash_customer_node {
    char id[HASH_ID_SIZE];
    AssocList restaurants;
    struct hash_customer_node* next;
} HashCustomerNode;

typedef struct hash_restaurant_node {
    char id[HASH_ID_SIZE];
    AssocList customers;
    struct hash_restaurant_node* next;
} HashRestaurantNode;

typedef struct hash_m2m_db {
    HashCustomerNode* customerTable[HASH_TABLE_SIZE];
    HashRestaurantNode* restaurantTable[HASH_TABLE_SIZE];
} HashM2MDB;

void hash_db_init(HashM2MDB* db);
int hash_insert_customer(HashM2MDB* db, const char* customerID);
int hash_insert_restaurant(HashM2MDB* db, const char* restaurantID);
HashCustomerNode* hash_find_customer(HashM2MDB* db, const char* customerID);
HashRestaurantNode* hash_find_restaurant(HashM2MDB* db, const char* restaurantID);
int hash_place_order(HashM2MDB* db, const char* customerID, const char* restaurantID);
void hash_db_destroy(HashM2MDB* db);

#endif
