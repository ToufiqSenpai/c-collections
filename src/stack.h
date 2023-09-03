#ifndef COLLECTION_STACK_H
#define COLLECTION_STACK_H
#include "common.h"

typedef struct Stack {
    void **elements;
    size_t size;
    size_t capacity;
    size_t type_size;
} Stack;

static bool stack_expand_capacity(Stack *stack);
Stack *stack_new(size_t type_size);
void *stack_peek(Stack *stack);
void *stack_pop(Stack *stack);
void *stack_push(Stack *stack, void *element);

#endif //COLLECTION_STACK_H
