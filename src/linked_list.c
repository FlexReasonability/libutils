#include "linked_list.h"

#include <stdlib.h>

/**
 * @brief Initialize a new linked list.
 *
 * This function allocates and initializes a new linked list. It sets the head
 * of the list to NULL, the size to 0, and stores the function pointer
 * `free_data` to handle memory deallocation of the data elements.
 *
 * @param[in] free_data Function pointer used to free the data stored in the
 * list nodes. This function will be called on each node's data when the list is
 * destroyed.
 * @return Pointer to the newly created LinkedList, or NULL if memory allocation
 * fails.
 */
LinkedList *init_linked_list(void (*free_data)(void *))
{
    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list)
        return NULL;
    list->head = NULL;
    list->size = 0;
    list->free_data = free_data;
    return list;
}

/**
 * @brief Append a node at the end of the linked list.
 *
 * This function creates a new node with the provided data and appends it
 * at the end of the linked list.
 *
 * @param[in] list Pointer to the linked list.
 * @param[in] data Pointer to the data to store in the new node.
 * @return void
 */
void append(LinkedList *list, void *data)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = NULL;

    if (!list->head)
    {
        list->head = new_node;
    }
    else
    {
        Node *current = list->head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

/**
 * @brief Insert a node at a specified position in the linked list.
 *
 * This function creates a new node with the provided data and inserts it
 * at the specified position in the linked list. If the position is out of
 * bounds, the function does nothing.
 *
 * @param[in] list Pointer to the linked list.
 * @param[in] data Pointer to the data to store in the new node.
 * @param[in] position The position at which to insert the new node (0-based
 * index). If position is greater than the size of the list, the function will
 * append the node at the end.
 * @return void
 */
void insert_at(LinkedList *list, void *data, size_t position)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return;
    new_node->data = data;

    if (position == 0 || !list->head)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        Node *current = list->head;
        size_t index = 0;

        while (current->next && index < position - 1)
        {
            current = current->next;
            index++;
        }

        new_node->next = current->next;
        current->next = new_node;
    }
    list->size++;
}

/**
 * @brief Remove the node at a specified position in the linked list.
 *
 * This function removes the node at the given position in the linked list.
 * If the position is out of bounds, the function does nothing.
 *
 * @param[in] list Pointer to the linked list.
 * @param[in] position The position of the node to remove (0-based index).
 * @return void
 */
void remove_at(LinkedList *list, size_t position)
{
    if (!list->head || position >= list->size)
        return;

    Node *current = list->head;

    if (position == 0)
    {
        list->head = current->next;
        if (list->free_data)
        {
            list->free_data(current->data);
        }
        free(current);
    }
    else
    {
        Node *previous = NULL;
        size_t index = 0;
        while (current && index < position)
        {
            previous = current;
            current = current->next;
            index++;
        }

        if (current)
        {
            previous->next = current->next;
            if (list->free_data)
            {
                list->free_data(current->data);
            }
            free(current);
        }
    }
    list->size--;
}

/**
 * @brief Get the data at a specified position in the linked list.
 *
 * This function returns a pointer to the data stored in the node at the given
 * position in the linked list. If the position is out of bounds, it returns
 * NULL.
 *
 * @param[in] list Pointer to the linked list.
 * @param[in] position The position of the node to retrieve (0-based index).
 * @return Pointer to the data stored at the specified position, or NULL if out
 * of bounds.
 */
void *get_at(LinkedList *list, size_t position)
{
    if (!list->head || position >= list->size)
        return NULL;

    Node *current = list->head;
    size_t index = 0;

    while (current && index < position)
    {
        current = current->next;
        index++;
    }

    return current ? current->data : NULL;
}

/**
 * @brief Free the entire linked list and its data.
 *
 * This function iterates through the linked list, freeing each node and its
 * data. If a free_data function is provided, it is used to free the data in
 * each node. Be careful: all the data in the list will be freed.
 *
 * @param[in] list Pointer to the linked list to free.
 * @return void
 */
void free_linked_list(LinkedList *list)
{
    if (!list)
        return;

    Node *current = list->head;
    while (current != NULL)
    {
        Node *next_node = current->next;

        if (list->free_data)
        {
            list->free_data(current->data);
        }

        free(current);
        current = next_node;
    }
    free(list);
}
