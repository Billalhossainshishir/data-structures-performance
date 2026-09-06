#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_m2m_db.h"

static int max_int(int a, int b) { return a > b ? a : b; }

static int customer_height(AVLCustomerNode* node) { return node == NULL ? 0 : node->height; }
static int restaurant_height(AVLRestaurantNode* node) { return node == NULL ? 0 : node->height; }

static AVLCustomerNode* create_customer_node(const char* id) {
    AVLCustomerNode* node = (AVLCustomerNode*)malloc(sizeof(AVLCustomerNode));
    if (node == NULL) return NULL;
    snprintf(node->id, sizeof(node->id), "%s", id);
    assoc_list_init(&node->restaurants);
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

static AVLRestaurantNode* create_restaurant_node(const char* id) {
    AVLRestaurantNode* node = (AVLRestaurantNode*)malloc(sizeof(AVLRestaurantNode));
    if (node == NULL) return NULL;
    snprintf(node->id, sizeof(node->id), "%s", id);
    assoc_list_init(&node->customers);
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

static AVLCustomerNode* rotate_customer_right(AVLCustomerNode* y) {
    AVLCustomerNode* x = y->left;
    AVLCustomerNode* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max_int(customer_height(y->left), customer_height(y->right));
    x->height = 1 + max_int(customer_height(x->left), customer_height(x->right));
    return x;
}

static AVLCustomerNode* rotate_customer_left(AVLCustomerNode* x) {
    AVLCustomerNode* y = x->right;
    AVLCustomerNode* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max_int(customer_height(x->left), customer_height(x->right));
    y->height = 1 + max_int(customer_height(y->left), customer_height(y->right));
    return y;
}

static AVLCustomerNode* insert_customer(AVLCustomerNode* root, const char* id, int* inserted) {
    if (root == NULL) {
        *inserted = 1;
        return create_customer_node(id);
    }
    int cmp = strcmp(id, root->id);
    if (cmp < 0) root->left = insert_customer(root->left, id, inserted);
    else if (cmp > 0) root->right = insert_customer(root->right, id, inserted);
    else { *inserted = 0; return root; }

    root->height = 1 + max_int(customer_height(root->left), customer_height(root->right));
    int balance = customer_height(root->left) - customer_height(root->right);

    if (balance > 1 && strcmp(id, root->left->id) < 0) return rotate_customer_right(root);
    if (balance < -1 && strcmp(id, root->right->id) > 0) return rotate_customer_left(root);
    if (balance > 1 && strcmp(id, root->left->id) > 0) {
        root->left = rotate_customer_left(root->left);
        return rotate_customer_right(root);
    }
    if (balance < -1 && strcmp(id, root->right->id) < 0) {
        root->right = rotate_customer_right(root->right);
        return rotate_customer_left(root);
    }
    return root;
}

static AVLRestaurantNode* rotate_restaurant_right(AVLRestaurantNode* y) {
    AVLRestaurantNode* x = y->left;
    AVLRestaurantNode* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max_int(restaurant_height(y->left), restaurant_height(y->right));
    x->height = 1 + max_int(restaurant_height(x->left), restaurant_height(x->right));
    return x;
}

static AVLRestaurantNode* rotate_restaurant_left(AVLRestaurantNode* x) {
    AVLRestaurantNode* y = x->right;
    AVLRestaurantNode* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max_int(restaurant_height(x->left), restaurant_height(x->right));
    y->height = 1 + max_int(restaurant_height(y->left), restaurant_height(y->right));
    return y;
}

static AVLRestaurantNode* insert_restaurant(AVLRestaurantNode* root, const char* id, int* inserted) {
    if (root == NULL) {
        *inserted = 1;
        return create_restaurant_node(id);
    }
    int cmp = strcmp(id, root->id);
    if (cmp < 0) root->left = insert_restaurant(root->left, id, inserted);
    else if (cmp > 0) root->right = insert_restaurant(root->right, id, inserted);
    else { *inserted = 0; return root; }

    root->height = 1 + max_int(restaurant_height(root->left), restaurant_height(root->right));
    int balance = restaurant_height(root->left) - restaurant_height(root->right);

    if (balance > 1 && strcmp(id, root->left->id) < 0) return rotate_restaurant_right(root);
    if (balance < -1 && strcmp(id, root->right->id) > 0) return rotate_restaurant_left(root);
    if (balance > 1 && strcmp(id, root->left->id) > 0) {
        root->left = rotate_restaurant_left(root->left);
        return rotate_restaurant_right(root);
    }
    if (balance < -1 && strcmp(id, root->right->id) < 0) {
        root->right = rotate_restaurant_right(root->right);
        return rotate_restaurant_left(root);
    }
    return root;
}

void avl_db_init(AVLM2MDB* db) {
    if (db == NULL) return;
    db->customerRoot = NULL;
    db->restaurantRoot = NULL;
}

int avl_insert_customer(AVLM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL || strlen(customerID) == 0) return 0;
    int inserted = 0;
    db->customerRoot = insert_customer(db->customerRoot, customerID, &inserted);
    return inserted;
}

int avl_insert_restaurant(AVLM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL || strlen(restaurantID) == 0) return 0;
    int inserted = 0;
    db->restaurantRoot = insert_restaurant(db->restaurantRoot, restaurantID, &inserted);
    return inserted;
}

AVLCustomerNode* avl_find_customer(AVLM2MDB* db, const char* customerID) {
    if (db == NULL || customerID == NULL) return NULL;
    AVLCustomerNode* current = db->customerRoot;
    while (current != NULL) {
        int cmp = strcmp(customerID, current->id);
        if (cmp == 0) return current;
        current = cmp < 0 ? current->left : current->right;
    }
    return NULL;
}

AVLRestaurantNode* avl_find_restaurant(AVLM2MDB* db, const char* restaurantID) {
    if (db == NULL || restaurantID == NULL) return NULL;
    AVLRestaurantNode* current = db->restaurantRoot;
    while (current != NULL) {
        int cmp = strcmp(restaurantID, current->id);
        if (cmp == 0) return current;
        current = cmp < 0 ? current->left : current->right;
    }
    return NULL;
}

int avl_place_order(AVLM2MDB* db, const char* customerID, const char* restaurantID) {
    AVLCustomerNode* customer = avl_find_customer(db, customerID);
    AVLRestaurantNode* restaurant = avl_find_restaurant(db, restaurantID);
    if (customer == NULL || restaurant == NULL) return 0;
    if (assoc_list_contains(&customer->restaurants, restaurantID)) return 0;
    int a = assoc_list_insert(&customer->restaurants, restaurantID);
    int b = assoc_list_insert(&restaurant->customers, customerID);
    return a && b;
}

static void destroy_customer_tree(AVLCustomerNode* root) {
    if (root == NULL) return;
    destroy_customer_tree(root->left);
    destroy_customer_tree(root->right);
    assoc_list_destroy(&root->restaurants);
    free(root);
}

static void destroy_restaurant_tree(AVLRestaurantNode* root) {
    if (root == NULL) return;
    destroy_restaurant_tree(root->left);
    destroy_restaurant_tree(root->right);
    assoc_list_destroy(&root->customers);
    free(root);
}

void avl_db_destroy(AVLM2MDB* db) {
    if (db == NULL) return;
    destroy_customer_tree(db->customerRoot);
    destroy_restaurant_tree(db->restaurantRoot);
    db->customerRoot = NULL;
    db->restaurantRoot = NULL;
}
