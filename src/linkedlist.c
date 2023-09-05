#include "linkedlist.h"

/**
 * Append a specified element to the end of this list.
 *
 * @param head pointer of the head node
 * @param data to append to the node
 * @param type_size size of the data type
 * @return COLLECTION_OK if the process is success, else return COLLECTION_ERR_ALLOC if the allocation memory is error.
 */
bool linked_list_add(LinkedList **head, void *element, size_t type_size) {
  // If the head node is null, we need to create the instance of this node.
  if(*head == NULL) {
    LinkedList *new_node = linked_list_create(element, type_size);

    if(new_node == NULL)
      return false;

    *head = new_node;
    return true;
  }

  // When the next node is not null, loop the node until the next node is null.
  LinkedList *current_head = *head;
  while(current_head->next != NULL)
    current_head = current_head->next;

  // After we get the end of the node, assign next node to the new node with the data.
  // If allocation memory is failed, return COLLECTION_ERR_ALLOC.
  if((current_head->next = linked_list_create(element, type_size)) == NULL)
    return false;

  return true;
}

void linked_list_clear(LinkedList **head) {
  LinkedList *current_head = *head;
  LinkedList *next_node;

  while(current_head != NULL) {
    next_node = current_head->next;

    free(current_head->element);
    free(current_head);

    current_head = next_node;
  }

  *head = NULL;
}

bool linked_list_contains(LinkedList *head, void *data) {
  LinkedList *current_head = head;
  while(current_head != NULL) {
    if(current_head->element == data) {
      return true;
    }
  }

  return false;
}

/**
 * Create a new node assign the element.
 *
 * @param head pointer of the head node
 * @param data data to append to the node
 * @param type_size size of the data type
 * @return COLLECTION_OK if the process is success, else return COLLECTION_ERR_ALLOC if the allocation memory is error.
 */
LinkedList *linked_list_create(void *data, size_t type_size) {
  LinkedList *new_node = (LinkedList*) malloc(sizeof(LinkedList));

  if(new_node == NULL)
    return NULL;

  new_node->element = malloc(type_size);
  new_node->next = NULL;

  for(int i = 0; i < type_size; i++)
    *(char*) (new_node->element + i) = *(char*)(data + i);

  return new_node;
}

void linked_list_foreach(LinkedList *head, void (*action)(const void*)) {
  LinkedList *current_head = head;
  while(current_head != NULL) {
    action(current_head->element);
    current_head = current_head->next;
  }
}

void *linked_list_get(LinkedList *head, size_t index) {
  LinkedList *current_head = head;
  size_t i = 0;

  while(current_head != NULL) {
    if(i == index) {
      return current_head->element;
    }

    current_head = current_head->next;
    i++;
  }

  return NULL;
}

void *linked_list_get_first(LinkedList *head) {
  if(head == NULL)
    return NULL;
  return head->element;
}

void *linked_list_get_last(LinkedList *head) {
  LinkedList *current_head = head;
  while(current_head != NULL)
    current_head = current_head->next;

  return current_head->element;
}

ssize_t linked_list_index_of(LinkedList *head, void *element) {
  ssize_t index = 0;
  LinkedList *current_head = head;

  while(current_head != NULL) {
    if(current_head->element == element) {
      return index;
    }

    current_head = current_head->next;
    index++;
  }

  return -1;
}

void *linked_list_remove(LinkedList **head, void *element) {

}

void *linked_list_remove_at(LinkedList **head, size_t index) {
  LinkedList *current_head = *head;
  LinkedList *previous_head = NULL;

  if(index == 0) {
    *head = current_head->next;
    void *removed_element = current_head->element;

    free(current_head);

    return removed_element;
  }

  size_t i = 0;
  while(current_head != NULL && i != index) {
    previous_head = current_head;
    current_head = current_head->next;

    i++;
  }

  if(current_head == NULL) {
    return NULL;
  }

  void *removed_element = current_head->element;

  previous_head->next = current_head->next;
  free(current_head);

  return removed_element;
}

void linked_list_reverse(LinkedList **head) {
  LinkedList *current = *head, 
  *previous = NULL, 
  *next;

  while(current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *head = previous;
}

ssize_t linked_list_size(LinkedList *head) {
  LinkedList *current_head = head;

  if(current_head == NULL)
    return -1;

  ssize_t current_count = 0;
  do
    current_count++;
  while ((current_head = current_head->next) != NULL);

  return current_count;
}