#ifndef COLLECTION_LINKEDLIST_H
#define COLLECTION_LINKEDLIST_H
#include "common.h"

typedef struct LinkedList {
    void *element;
    struct LinkedList *next;
} LinkedList;

bool linked_list_add(LinkedList **head, void *data, size_t type_size);
void linked_list_clear(LinkedList **head);
bool linked_list_contains(LinkedList *head, void *data);
LinkedList *linked_list_create(void *data, size_t type_size);
void linked_list_foreach(LinkedList *head, void (*action)(const void*));
void *linked_list_get(LinkedList *head, size_t index);
void *linked_list_get_first(LinkedList *head);
void *linked_list_get_last(LinkedList *head);
ssize_t linked_list_index_of(LinkedList *head, void *element);
void *linked_list_remove(LinkedList **head, void *element);
void *linked_list_remove_at(LinkedList **head, size_t index);
void linked_list_reverse(LinkedList **head);
ssize_t linked_list_size(LinkedList *head);

#endif //COLLECTION_LINKEDLIST_H
