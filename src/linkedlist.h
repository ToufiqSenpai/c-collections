//
// Created by hi on 29/08/2023.
//

#ifndef COLLECTION_LINKEDLIST_H
#define COLLECTION_LINKEDLIST_H
#include "common.h"

typedef struct LinkedListNode LinkedListNode;

bool linked_list_add(LinkedListNode **head, void *data, size_t type_size);
void linked_list_clear(LinkedListNode **head);
bool linked_list_contains(LinkedListNode *head, void *data);
LinkedListNode *linked_list_create(void *data, size_t type_size);
void linked_list_foreach(LinkedListNode *head, void (*action)(const void*));
void *linked_list_get(LinkedListNode *head, size_t index);
void *linked_list_get_first(LinkedListNode *head);
void *linked_list_get_last(LinkedListNode *head);
ssize_t linked_list_index_of(LinkedListNode *head, void *element);
void *linked_list_remove(LinkedListNode **head, void *element);
void *linked_list_remove_at(LinkedListNode **head, size_t index);
ssize_t linked_list_size(LinkedListNode *head);

#endif //COLLECTION_LINKEDLIST_H
