#ifndef ASSOC_LIST_H
#define ASSOC_LIST_H

typedef struct assoc_node {
    char id[20];
    struct assoc_node* next;
} AssocNode;

typedef struct assoc_list {
    AssocNode* head;
} AssocList;

void assoc_list_init(AssocList* list);
int assoc_list_insert(AssocList* list, const char* id);
int assoc_list_contains(const AssocList* list, const char* id);
void assoc_list_print(const AssocList* list);
void assoc_list_destroy(AssocList* list);

#endif
