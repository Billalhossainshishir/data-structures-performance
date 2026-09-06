#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assoc_list.h"

void assoc_list_init(AssocList* list) {
    if (list != NULL) list->head = NULL;
}

int assoc_list_contains(const AssocList* list, const char* id) {
    if (list == NULL || id == NULL) return 0;
    AssocNode* current = list->head;
    while (current != NULL) {
        int cmp = strcmp(current->id, id);
        if (cmp == 0) return 1;
        if (cmp > 0) return 0;
        current = current->next;
    }
    return 0;
}

int assoc_list_insert(AssocList* list, const char* id) {
    if (list == NULL || id == NULL || strlen(id) == 0) return 0;
    if (assoc_list_contains(list, id)) return 0;

    AssocNode* new_node = (AssocNode*)malloc(sizeof(AssocNode));
    if (new_node == NULL) return 0;
    snprintf(new_node->id, sizeof(new_node->id), "%s", id);
    new_node->next = NULL;

    if (list->head == NULL || strcmp(id, list->head->id) < 0) {
        new_node->next = list->head;
        list->head = new_node;
        return 1;
    }

    AssocNode* previous = NULL;
    AssocNode* current = list->head;
    while (current != NULL && strcmp(current->id, id) < 0) {
        previous = current;
        current = current->next;
    }
    previous->next = new_node;
    new_node->next = current;
    return 1;
}

void assoc_list_print(const AssocList* list) {
    if (list == NULL || list->head == NULL) {
        printf("(empty)\n");
        return;
    }
    AssocNode* current = list->head;
    while (current != NULL) {
        printf("%s%s", current->id, current->next ? " -> " : "\n");
        current = current->next;
    }
}

void assoc_list_destroy(AssocList* list) {
    if (list == NULL) return;
    AssocNode* current = list->head;
    while (current != NULL) {
        AssocNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}
