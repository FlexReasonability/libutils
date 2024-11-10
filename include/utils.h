#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct LinkedList
{
    struct Node *head;
    size_t size;
    void (*free_data)(void *data);
} LinkedList;

// linked list
LinkedList *init_linked_list(void (*free_data)(void *));
void append(LinkedList *list, void *data);
void insert_at(LinkedList *list, void *data, size_t position);
void remove_at(LinkedList *list, size_t position);
void *get_at(LinkedList *list, size_t position);
void free_linked_list(LinkedList *list);

// cloming soon

#endif /* UTILS_H */