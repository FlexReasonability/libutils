#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct LinkedList LinkedList;
typedef struct Stack Stack;

// linked list
LinkedList *init_linked_list(void (*free_data)(void *));
void append(LinkedList *list, void *data);
void insert_at(LinkedList *list, void *data, size_t position);
void remove_at(LinkedList *list, size_t position);
void *get_at(LinkedList *list, size_t position);
void foreach(LinkedList *list, void (*func)(void *));
LinkedList *map(LinkedList *list, void *(*func)(void *),
                void (*free_data)(void *));
LinkedList *filter(LinkedList *list, int (*predicate)(void *));
void sort(LinkedList *list, int (*cmp)(const void *, const void *));
void free_linked_list(LinkedList *list);

// stack
Stack *init_stack(void (*free_data)(void *data));
void push(Stack *stack, void *data);
void *pop(Stack *stack);
int is_empty(Stack *stack);
size_t length(Stack *stack);
void free_stack(Stack *stack);

#endif /* UTILS_H */