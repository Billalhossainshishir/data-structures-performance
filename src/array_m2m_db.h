#ifndef ARRAY_M2M_DB_H
#define ARRAY_M2M_DB_H

#include "assoc_list.h"

#define ARRAY_MAX_RECORDS 1000
#define ID_SIZE 20

typedef struct array_customer {
    char id[ID_SIZE];
    AssocList restaurants;
} ArrayCustomer;

typedef struct array_restaurant {
    char id[ID_SIZE];
    AssocList customers;
} ArrayRestaurant;

typedef struct array_m2m_db {
    ArrayCustomer customers[ARRAY_MAX_RECORDS];
    ArrayRestaurant restaurants[ARRAY_MAX_RECORDS];
    int customerCount;
    int restaurantCount;
} ArrayM2MDB;

void array_db_init(ArrayM2MDB* db);
int array_insert_customer(ArrayM2MDB* db, const char* customerID);
int array_insert_restaurant(ArrayM2MDB* db, const char* restaurantID);
ArrayCustomer* array_find_customer(ArrayM2MDB* db, const char* customerID);
ArrayRestaurant* array_find_restaurant(ArrayM2MDB* db, const char* restaurantID);
int array_place_order(ArrayM2MDB* db, const char* customerID, const char* restaurantID);
void array_db_destroy(ArrayM2MDB* db);

#endif
