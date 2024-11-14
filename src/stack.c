#include <stdlib.h>

#include "node.h"

struct Stack
{
    struct Node *head;
    size_t size;
    void (*free_data)(void *data);
};

/**
 * @brief Initializes a new stack.
 *
 * @param free_data A function pointer for freeing the data of each node, used
 * during stack destruction. Pass NULL if data does not require special handling
 * for freeing.
 * @return Stack* A pointer to the newly created stack, or NULL if memory
 * allocation fails.
 */
Stack *init_stack(void (*free_data)(void *data))
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        return NULL;
    }
    stack->head = NULL;
    stack->size = 0;
    stack->free_data = free_data;
    return stack;
}

/**
 * @brief Pushes a new element onto the stack.
 *
 * @param stack The stack on which to push the data.
 * @param data A pointer to the data to push onto the stack.
 */
void push(Stack *stack, void *data)
{
    if (!stack)
        return;

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return;

    new_node->data = data;
    new_node->next = stack->head;
    stack->head = new_node;
    stack->size++;
}

/**
 * @brief Pops the top element from the stack.
 *
 * @param stack The stack from which to pop the element.
 * @return void* A pointer to the data of the popped element, or NULL if the
 * stack is empty. Note: The caller is responsible for freeing the data if
 * necessary.
 */
void *pop(Stack *stack)
{
    if (!stack || !stack->head)
        return NULL;

    Node *top_node = stack->head;
    void *data = top_node->data;
    stack->head = top_node->next;
    free(top_node);
    stack->size--;
    return data;
}

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack The stack to check.
 * @return int Returns 1 if the stack is empty, 0 otherwise.
 */
int is_empty(Stack *stack)
{
    return stack->size == 0;
}

/**
 * @brief Returns the current number of elements in the stack.
 *
 * @param stack The stack whose length is queried.
 * @return size_t The number of elements in the stack.
 */
size_t length(Stack *stack)
{
    return stack ? stack->size : 0;
}

/**
 * @brief Frees all elements in the stack and the stack itself.
 *
 * @param stack The stack to free. This function will free each node's data
 * using the provided free_data function if not NULL.
 */
void free_stack(Stack *stack)
{
    if (!stack)
        return;

    Node *current = stack->head;
    while (current)
    {
        Node *next = current->next;
        if (stack->free_data)
        {
            stack->free_data(current->data);
        }
        free(current);
        current = next;
    }
    free(stack);
}
