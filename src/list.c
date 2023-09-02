#include "list.h"

#define DEFAULT_CAPACITY 8

/**
 * Appends the specified element to the end of this list.
 *
 * @param list instance
 * @param element element to be appended to this list
 * @return true if the element success added, or false if something error.
 */
bool list_add(List *list, void *element) {
  if(list->size >= list->capacity) {
    if(list_expand_capacity(list))
      return false;
  }

  list->elements[list->size] = element;
  list->size++;

  return true;
}

/**
 * Clear / free the list element and list instance
 *
 * @param list instance
 */
void list_clear(List *list) {
  for(size_t i = 0; i < list->size; i++) {
    free(list->elements[i]);
  }
  free(list);
}

/**
 * Returns true if this list contains the specified element.
 *
 * @param list instance
 * @param element element whose presence in this list is to be tested
 * @return true if this list contains the specified element
 */
bool list_contains(List *list, void *element) {
  for(size_t i = 0; i < list->size; i++) {
    if(list->elements[i] == element)
      return true;
  }
  return false;
}

/**
 * Increase capacity of list 2 times
 *
 * @param list instance
 * @return true if operation is success, or false if something error.
 */
static bool list_expand_capacity(List *list) {
  void **new_elements = (void**) malloc(list->capacity * list->type_size);

  if(!new_elements)
    return false;

  list->capacity *= 2;

  memcpy(new_elements, list->elements, list->size * sizeof(void*));
  free(list->elements);

  list->elements = new_elements;

  return true;
}

/**
 * Iterate all elements by calling callback function
 *
 * @param list instance
 * @param action function pointer callback
 */
void list_foreach(List *list, void (*action)(const void*)) {
  for(int i = 0; i < list->size; i++) {
    action(list->elements[i]);
  }
}

/**
 * Returns the element at the specified position in this list.
 *
 * @param list instance
 * @param index index of the element to return
 * @return the element at the specified position in this list
 */
void *list_get(List *list, size_t index) {
  if(index >= list->size)
    return NULL;

  return list->elements[index];
}

/**
 * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
 *
 * @param list instance
 * @param element element to search for
 * @return the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element
 */
ssize_t list_index_of(List *list, void *element) {
  ssize_t i;

  for(i = 0; i < list->size; i++) {
    if(list->elements[i] == element)
      return i;
  }

  return -1;
}

/**
 * Returns true if this list contains no elements.
 *
 * @param list
 * @return true if this list contains no elements
 */
bool list_is_empty(List *list) {
  return list->size == 0;
}

/**
 * Initialize / create a new instance
 *
 * @param type_size size of data type
 * @return List pointer if success, else return NULL if something error.
 */
List *list_new(size_t type_size) {
  List *list = (List*) malloc(sizeof(List));

  if(list == NULL) return NULL;

  list->elements = (void*) malloc(type_size * DEFAULT_CAPACITY);
  list->size = 0;
  list->capacity = DEFAULT_CAPACITY;
  list->type_size = type_size;

  return list;
}

/**
 * Removes the first occurrence of the specified element from this list, if it is present. If the list does not contain the element, it is unchanged.
 *
 * @param list instance
 * @param element element to be removed from this list, if present
 * @return true if this list contained the specified element
 */
void *list_remove(List *list, void *element) {
  size_t index = list_index_of(list, element);
  return index != -1 ? list_remove_at(list, index) : NULL;
}

/**
 * Removes the element at the specified position in this list. Shifts any subsequent elements to the left (subtracts one from their indices).
 *
 * @param list instance
 * @param index the index of the element to be removed
 * @return the element that was removed from the list
 */
void *list_remove_at(List *list, size_t index) {
  if(index >= list->size) {
    return NULL;
  }

  void *removed_element = list->elements[index];

  if(index < list->size - 1) {
    memmove(&(list->elements[index]),
            &(list->elements[index + 1]),
            (list->size - 1 - index) * sizeof(void*));
  }
  list->size--;

  return removed_element;
}

/**
 * Removes all of the elements of this collection that satisfy the given predicate.
 *
 * @param list instance
 * @param predicate a predicate which returns true for elements to be removed
 * @return true if any elements were removed
 */
bool list_remove_if(List *list, bool(*predicate)(const void*)) {
  for(size_t i = 0; i < list->size; i++) {
    if(predicate(list->elements[i]))
      free(list_remove_at(list, i));
  }

  return true;
}