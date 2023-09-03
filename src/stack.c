#include "stack.h"

#define DEFAULT_CAPACITY 8

static bool stack_expand_capacity(Stack *stack) {
  void **new_elements = (void**) malloc(stack->capacity * stack->type_size);

  if(new_elements == NULL) return false;

  stack->capacity *= 2;

  memcpy(new_elements, stack->elements, stack->size * stack->type_size);
  free(stack->elements);

  stack->elements = new_elements;

  return true;
}

Stack *stack_new(size_t type_size) {
  Stack *stack = (Stack*) malloc(sizeof(Stack));

  if(stack == NULL) return NULL;

  stack->elements = malloc(DEFAULT_CAPACITY * type_size);
  stack->size = 0;
  stack->capacity = DEFAULT_CAPACITY;
  stack->type_size = type_size;

  return stack;
}

void *stack_peek(Stack *stack) {
  void *peeked_element = (void*) malloc(stack->type_size);
  peeked_element = stack->elements + (stack->size - 1) * stack->type_size;

  return peeked_element;
}

void *stack_pop(Stack *stack) {
  void *source = (char*) stack->elements + (stack->size - 1) * stack->type_size;
  void *removed_element = (void*) malloc(stack->type_size);

  if(removed_element == NULL) return NULL;

  memcpy(removed_element, source, stack->type_size);
  stack->size--;

  return removed_element;
}

void *stack_push(Stack *stack, void *element) {
  if(stack->size >= stack->capacity) {
    if(!stack_expand_capacity(stack)) return false;
  }

  void *target = (char*) stack->elements + stack->size * stack->type_size;
  memcpy(target, element, stack->type_size);

  stack->size++;

  return element;
}