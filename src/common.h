//
// Created by hi on 24/08/2023.
//

#ifndef COLLECTIONS_COMMON_H
#define COLLECTIONS_COMMON_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum CollectionStatus {
    COLLECTION_OK,

    COLLECTION_ERR_OUT_OF_BOUND,
    COLLECTION_ERR_ALLOC,
    COLLECTION_ERR_NOT_FOUND,
    COLLECTION_ERR_NULL_POINTER
} CollectionStatus;

#endif //COLLECTIONS_COMMON_H
