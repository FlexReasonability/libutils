#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

#include "../include/utils.h"

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

#endif