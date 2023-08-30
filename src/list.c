#include "list.h"

#define DEFAULT_CAPACITY 8

typedef struct List {
    void **elements;
    size_t size;
    size_t capacity;
} List;

CollectionStatus list_init(List *list) {
  list->size = 0;
  list->capacity = DEFAULT_CAPACITY;

  return COLLECTION_OK;
}

/**
 * Increase capacity of list 2 times
 * @param list list instance
 * @return COLLECTION_OK if the
 */
CollectionStatus list_expand_capacity(List *list) {
  void **new_elements = (void**) malloc(list->capacity * sizeof(void*));

  if(!new_elements)
    return COLLECTION_ERR_ALLOC;

  list->capacity *= 2;

  memcpy(new_elements, list->elements, list->size * sizeof(void*));
  free(list->elements);

  list->elements = new_elements;

  return COLLECTION_OK;
}

CollectionStatus list_get(List *list, size_t index, void **out) {
  if(index >= list->size)
    return COLLECTION_ERR_OUT_OF_BOUND;

  *out = list->elements[index];
  return COLLECTION_OK;
}

CollectionStatus list_add(List *list, void *element) {
  if(list->size >= list->capacity) {
    CollectionStatus expand_status = list_expand_capacity(list);

    if(expand_status != COLLECTION_OK)
      return expand_status;
  }

  list->elements[list->size] = element;
  list->size++;

  return COLLECTION_OK;
}

CollectionStatus list_remove(List *list, void *element, void **out) {
  size_t index;
  CollectionStatus index_status = list_index_of(list, element, &index);

  if(index_status == COLLECTION_ERR_OUT_OF_BOUND)
    return COLLECTION_ERR_NOT_FOUND;

  if(index != list->size - 1)  {
    memmove(&(list->elements[index]),
            &(list->elements[index + 1]),
            (list->size - 1 - index) * sizeof(void*));
  }
  list->size--;

  if(out)
    *out = element;

  return COLLECTION_OK;
}

CollectionStatus list_remove_at(List *list, size_t index, void **out) {
  if(index >= list->size) {
    return COLLECTION_ERR_OUT_OF_BOUND;
  }

  if(out)
    *out = list->elements[index];

  if(index < list->size - 1) {
    memmove(&(list->elements[index]),
            &(list->elements[index + 1]),
            (list->size - 1 - index) * sizeof(void*));
  }

  list->size--;

  return COLLECTION_OK;
}

CollectionStatus list_index_of(List *list, void *element, size_t *index) {
  size_t i;

  for(i = 0; i < list->size; i++) {
    if(list->elements[i] == element) {
      *index = i;
      return COLLECTION_OK;
    }
  }

  return COLLECTION_ERR_OUT_OF_BOUND;
}

CollectionStatus list_foreach(List *list, void (*action)(const void*)) {
  for(int i = 0; i < list->size; i++) {
    action(list->elements[i]);
  }

  return COLLECTION_OK;
}

CollectionStatus list_filter(List *list, int (*predicate)(const void*)) {

}

void foreach_action(const void *element) {
  printf("%s", (char*) element);
}

int main() {
  List list;

  list_init(&list);
  list_add(&list, "Muhammad");
  list_add(&list, "Taufiqurrahman");
  list_foreach(&list, foreach_action);


}