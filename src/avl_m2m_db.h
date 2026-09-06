#ifndef AVL_M2M_DB_H
#define AVL_M2M_DB_H

#include "assoc_list.h"

#define AVL_ID_SIZE 20

typedef struct avl_customer_node {
    char id[AVL_ID_SIZE];
    AssocList restaurants;
    int height;
    struct avl_customer_node* left;
    struct avl_customer_node* right;
} AVLCustomerNode;

typedef struct avl_restaurant_node {
    char id[AVL_ID_SIZE];
    AssocList customers;
    int height;
    struct avl_restaurant_node* left;
    struct avl_restaurant_node* right;
} AVLRestaurantNode;

typedef struct avl_m2m_db {
    AVLCustomerNode* customerRoot;
    AVLRestaurantNode* restaurantRoot;
} AVLM2MDB;

void avl_db_init(AVLM2MDB* db);
int avl_insert_customer(AVLM2MDB* db, const char* customerID);
int avl_insert_restaurant(AVLM2MDB* db, const char* restaurantID);
AVLCustomerNode* avl_find_customer(AVLM2MDB* db, const char* customerID);
AVLRestaurantNode* avl_find_restaurant(AVLM2MDB* db, const char* restaurantID);
int avl_place_order(AVLM2MDB* db, const char* customerID, const char* restaurantID);
void avl_db_destroy(AVLM2MDB* db);

#endif
