//
// Created by hi on 24/08/2023.
//

#ifndef COLLECTIONS_LIST_H
#define COLLECTIONS_LIST_H
#include "common.h"

typedef struct List List;

CollectionStatus list_init(List *list);
CollectionStatus list_expand_capacity(List *list);
CollectionStatus list_get(List *list, size_t index, void **out);
CollectionStatus list_add(List *list, void *element);
CollectionStatus list_remove(List *list, void *element, void **out);
CollectionStatus list_remove_at(List *list, size_t index, void **out);
CollectionStatus list_index_of(List *list, void *element, size_t *index);
CollectionStatus list_foreach(List* list, void (*action)(const void*));

#endif //COLLECTIONS_LIST_H
