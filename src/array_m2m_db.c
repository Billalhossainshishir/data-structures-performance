#include <stdio.h>
#include <string.h>
#include "array_m2m_db.h"

void array_db_init(ArrayM2MDB* db) {
    if (db == NULL) return;
    db->customerCount = 0;
    db->restaurantCount = 0;
}

ArrayCustomer* array_find_customer(ArrayM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL) return NULL;
    for (int i = 0; i < db->customerCount; i++) {
        if (strcmp(db->customers[i].id, customerID) == 0) return &db->customers[i];
    }
    return NULL;
}

ArrayRestaurant* array_find_restaurant(ArrayM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL) return NULL;
    for (int i = 0; i < db->restaurantCount; i++) {
        if (strcmp(db->restaurants[i].id, restaurantID) == 0) return &db->restaurants[i];
    }
    return NULL;
}

int array_insert_customer(ArrayM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL || strlen(customerID) == 0) return 0;
    if (db->customerCount >= ARRAY_MAX_RECORDS || array_find_customer(db, customerID) != NULL) return 0;
    snprintf(db->customers[db->customerCount].id, sizeof(db->customers[db->customerCount].id), "%s", customerID);
    assoc_list_init(&db->customers[db->customerCount].restaurants);
    db->customerCount++;
    return 1;
}

int array_insert_restaurant(ArrayM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL || strlen(restaurantID) == 0) return 0;
    if (db->restaurantCount >= ARRAY_MAX_RECORDS || array_find_restaurant(db, restaurantID) != NULL) return 0;
    snprintf(db->restaurants[db->restaurantCount].id, sizeof(db->restaurants[db->restaurantCount].id), "%s", restaurantID);
    assoc_list_init(&db->restaurants[db->restaurantCount].customers);
    db->restaurantCount++;
    return 1;
}

int array_place_order(ArrayM2MDB* db, const char* customerID, const char* restaurantID) {
    ArrayCustomer* customer = array_find_customer(db, customerID);
    ArrayRestaurant* restaurant = array_find_restaurant(db, restaurantID);
    if (customer == NULL || restaurant == NULL) return 0;
    if (assoc_list_contains(&customer->restaurants, restaurantID)) return 0;
    int a = assoc_list_insert(&customer->restaurants, restaurantID);
    int b = assoc_list_insert(&restaurant->customers, customerID);
    return a && b;
}

void array_db_destroy(ArrayM2MDB* db) {
    if (db == NULL) return;
    for (int i = 0; i < db->customerCount; i++) assoc_list_destroy(&db->customers[i].restaurants);
    for (int i = 0; i < db->restaurantCount; i++) assoc_list_destroy(&db->restaurants[i].customers);
    db->customerCount = 0;
    db->restaurantCount = 0;
}
