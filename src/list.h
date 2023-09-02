#ifndef COLLECTIONS_LIST_H
#define COLLECTIONS_LIST_H
#include "common.h"

typedef struct List {
    void **elements;
    size_t size;
    size_t capacity;
    size_t type_size;
} List;

bool list_add(List *list, void *element);
void list_clear(List *list);
bool list_contains(List *list, void *element);
static bool list_expand_capacity(List *list);
void list_foreach(List* list, void (*action)(const void*));
void *list_get(List *list, size_t index);
ssize_t list_index_of(List *list, void *element);
List *list_new(size_t type_size);
void *list_remove(List *list, void *element);
void *list_remove_at(List *list, size_t index);
bool list_remove_if(List *list, bool (*predicate)(const void*));

#endif //COLLECTIONS_LIST_H
