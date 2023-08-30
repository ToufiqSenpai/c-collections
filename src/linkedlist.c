#include "linkedlist.h"

typedef struct LinkedListNode {
    void *data;
    LinkedListNode *next;
} LinkedListNode;

/**
 * Append a specified element to the end of this list.
 *
 * @param head pointer of the head node
 * @param data to append to the node
 * @param type_size size of the data type
 * @return COLLECTION_OK if the process is success, else return COLLECTION_ERR_ALLOC if the allocation memory is error.
 */
CollectionStatus linked_list_add(LinkedListNode **head, void *data, size_t type_size) {
  // If the head node is null, we need to create the instance of this node.
  if(*head == NULL) {
    LinkedListNode *new_node = NULL;

    if(linked_list_create(&new_node, data, type_size) == COLLECTION_ERR_ALLOC)
      return COLLECTION_ERR_ALLOC;

    *head = new_node;
    return COLLECTION_OK;
  }

  // When the next node is not null, loop the node until the next node is null.
  LinkedListNode *current_head = *head;
  while(current_head->next != NULL)
    current_head = current_head->next;

  // After we get the end of the node, assign next node to the new node with the data.
  // If allocation memory is failed, return COLLECTION_ERR_ALLOC.
  if(linked_list_create(&current_head->next, data, type_size) == COLLECTION_ERR_ALLOC)
    return COLLECTION_ERR_ALLOC;

  return COLLECTION_OK;
}

/**
 * Create a new node assign the element.
 *
 * @param head pointer of the head node
 * @param data data to append to the node
 * @param type_size size of the data type
 * @return COLLECTION_OK if the process is success, else return COLLECTION_ERR_ALLOC if the allocation memory is error.
 */
CollectionStatus linked_list_create(LinkedListNode **node, void *data, size_t type_size) {
  LinkedListNode *new_node = (LinkedListNode*) malloc(sizeof(LinkedListNode));

  if(new_node == NULL)
    return COLLECTION_ERR_ALLOC;

  new_node->data = malloc(type_size);
  new_node->next = NULL;

  for(int i = 0; i < type_size; i++)
    *(char*) (new_node->data + i) = *(char*)(data + i);

  *node = new_node;

  return COLLECTION_OK;
}

CollectionStatus linked_list_clear(LinkedListNode **head) {
  LinkedListNode *current_head = *head;
  LinkedListNode *next_node;

  while(current_head != NULL) {
    next_node = current_head->next;

    free(current_head->data);
    free(current_head);

    current_head = next_node;
  }

  *head = NULL;

  return COLLECTION_OK;
}

CollectionStatus linked_list_contains(LinkedListNode *head, void *data, bool *result) {
  LinkedListNode *current_head = head;
  while(current_head != NULL) {
    if(current_head->data == data) {
      *result = true;
      return COLLECTION_OK;
    }
  }

  *result = false;
  return COLLECTION_ERR_NOT_FOUND;
}

CollectionStatus linked_list_foreach(LinkedListNode *head, void (*action)(const void*)) {
  LinkedListNode *current_head = head;
  while(current_head != NULL) {
    action(current_head->data);
    current_head = current_head->next;
  }

  return COLLECTION_OK;
}

CollectionStatus linked_list_get(LinkedListNode *head, size_t index, void *out) {
  LinkedListNode *current_head = head;
  size_t i = 0;

  while(current_head != NULL) {
    if(i == index) {
      out == current_head->data;
      return COLLECTION_OK;
    }

    current_head = current_head->next;
    i++;
  }

  return COLLECTION_ERR_NOT_FOUND;
}

CollectionStatus linked_list_get_first(LinkedListNode *head, void *out) {
  if(head == NULL)
    return COLLECTION_ERR_NULL_POINTER;
  out = head->data;
  return COLLECTION_OK;
}

CollectionStatus linked_list_get_last(LinkedListNode *head, void *out) {
  LinkedListNode *current_head = head;
  while(current_head != NULL)
    current_head = current_head->next;

  out = current_head->data;

  return COLLECTION_OK;
}

CollectionStatus linked_list_remove_at(LinkedListNode **head, size_t index) {
  LinkedListNode *current_head = *head;
  LinkedListNode *previous_head = NULL;

  if(index == 0) {
    *head = current_head->next;

    free(current_head->data);
    free(current_head);

    return COLLECTION_OK;
  }

  int i = 0;
  while(current_head != NULL && i != index) {
    previous_head = current_head;
    current_head = current_head->next;

    i++;
  }

  if(current_head == NULL) {
    return COLLECTION_ERR_OUT_OF_BOUND;
  }

  previous_head->next = current_head->next;
  free(current_head->data);
  free(current_head);

  return COLLECTION_OK;
}

CollectionStatus linked_list_size(LinkedListNode *head, size_t *count) {
  LinkedListNode *current_head = head;

  if(current_head == NULL)
    return COLLECTION_ERR_NULL_POINTER;

  size_t current_count = 0;
  do
    current_count++;
  while ((current_head = current_head->next) != NULL);

  *count = current_count;

  return COLLECTION_OK;
}

void cb_foreach(const void *data) {
  printf("%s ", (char*)data);
}

int main() {
  LinkedListNode *main_node = NULL;

  char str1[] = "Nilou";
  char str2[] = "Istri";
  char str3[] = "Gw";

  linked_list_add(&main_node, str1, 6);
  linked_list_add(&main_node, str2, 6);
  linked_list_add(&main_node, str3, 3);

  size_t size1 = 0;

  linked_list_size(main_node, &size1);

  printf("%zu\n", size1);

  linked_list_foreach(main_node, cb_foreach);

  return 0;
}