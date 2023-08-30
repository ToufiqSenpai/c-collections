//
// Created by hi on 29/08/2023.
//

#ifndef COLLECTION_LINKEDLIST_H
#define COLLECTION_LINKEDLIST_H
#include "common.h"

typedef struct LinkedListNode LinkedListNode;

CollectionStatus linked_list_add(LinkedListNode **head, void *data, size_t type_size);
CollectionStatus linked_list_clear(LinkedListNode **head);
CollectionStatus linked_list_contains(LinkedListNode *head, void *data, bool *result);
CollectionStatus linked_list_create(LinkedListNode **head, void *data, size_t type_size);
CollectionStatus linked_list_foreach(LinkedListNode *head, void (*action)(const void*));
CollectionStatus linked_list_get(LinkedListNode *head, size_t index, void *out);
CollectionStatus linked_list_get_first(LinkedListNode *head, void *out);
CollectionStatus linked_list_get_last(LinkedListNode *head, void *out);
CollectionStatus linked_list_remove_at(LinkedListNode **head, size_t index);
CollectionStatus linked_list_size(LinkedListNode *head, size_t *count);

#endif //COLLECTION_LINKEDLIST_H
