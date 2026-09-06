#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_m2m_db.h"

static unsigned int hash_string(const char* id) {
    unsigned int hash = 0;
    if (id == NULL) return 0;
    for (int i = 0; id[i] != '\0'; i++) hash = (hash * 31) + (unsigned char)id[i];
    return hash % HASH_TABLE_SIZE;
}

void hash_db_init(HashM2MDB* db) {
    if (db == NULL) return;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        db->customerTable[i] = NULL;
        db->restaurantTable[i] = NULL;
    }
}

HashCustomerNode* hash_find_customer(HashM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL) return NULL;
    HashCustomerNode* current = db->customerTable[hash_string(customerID)];
    while (current != NULL) {
        if (strcmp(current->id, customerID) == 0) return current;
        current = current->next;
    }
    return NULL;
}

HashRestaurantNode* hash_find_restaurant(HashM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL) return NULL;
    HashRestaurantNode* current = db->restaurantTable[hash_string(restaurantID)];
    while (current != NULL) {
        if (strcmp(current->id, restaurantID) == 0) return current;
        current = current->next;
    }
    return NULL;
}

int hash_insert_customer(HashM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL || strlen(customerID) == 0 || hash_find_customer(db, customerID) != NULL) return 0;
    HashCustomerNode* node = (HashCustomerNode*)malloc(sizeof(HashCustomerNode));
    if (node == NULL) return 0;
    snprintf(node->id, sizeof(node->id), "%s", customerID);
    assoc_list_init(&node->restaurants);
    unsigned int index = hash_string(customerID);
    node->next = db->customerTable[index];
    db->customerTable[index] = node;
    return 1;
}

int hash_insert_restaurant(HashM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL || strlen(restaurantID) == 0 || hash_find_restaurant(db, restaurantID) != NULL) return 0;
    HashRestaurantNode* node = (HashRestaurantNode*)malloc(sizeof(HashRestaurantNode));
    if (node == NULL) return 0;
    snprintf(node->id, sizeof(node->id), "%s", restaurantID);
    assoc_list_init(&node->customers);
    unsigned int index = hash_string(restaurantID);
    node->next = db->restaurantTable[index];
    db->restaurantTable[index] = node;
    return 1;
}

int hash_place_order(HashM2MDB* db, const char* customerID, const char* restaurantID) {
    HashCustomerNode* customer = hash_find_customer(db, customerID);
    HashRestaurantNode* restaurant = hash_find_restaurant(db, restaurantID);
    if (customer == NULL || restaurant == NULL) return 0;
    if (assoc_list_contains(&customer->restaurants, restaurantID)) return 0;
    int a = assoc_list_insert(&customer->restaurants, restaurantID);
    int b = assoc_list_insert(&restaurant->customers, customerID);
    return a && b;
}

void hash_db_destroy(HashM2MDB* db) {
    if (db == NULL) return;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashCustomerNode* c = db->customerTable[i];
        while (c != NULL) {
            HashCustomerNode* next = c->next;
            assoc_list_destroy(&c->restaurants);
            free(c);
            c = next;
        }
        HashRestaurantNode* r = db->restaurantTable[i];
        while (r != NULL) {
            HashRestaurantNode* next = r->next;
            assoc_list_destroy(&r->customers);
            free(r);
            r = next;
        }
        db->customerTable[i] = NULL;
        db->restaurantTable[i] = NULL;
    }
}
