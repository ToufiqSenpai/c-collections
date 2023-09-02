#ifndef COLLECTION_STACK_H
#define COLLECTION_STACK_H
#include "common.h"

typedef struct Stack {
    void **elements;
    int size;
    int capacity;
} Stack;



#endif //COLLECTION_STACK_H
