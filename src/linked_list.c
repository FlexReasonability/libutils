#include <stdlib.h>
#include <string.h>

#include "node.h"

struct LinkedList
{
    struct Node *head;
    size_t size;
    void (*free_data)(void *data);
};

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
 * @brief Apply a function to each element in the linked list.
 *
 * This function iterates over each element in the list and applies the given
 * function to the data of each element.
 *
 * @param[in] list Pointer to the linked list.
 * @param[in] func Function to apply to each element's data.
 */
void foreach(LinkedList *list, void (*func)(void *))
{
    Node *current = list->head;
    while (current != NULL)
    {
        func(current->data);
        current = current->next;
    }
}

/**
 * @brief Create a new list by applying a transformation function to each
 * element.
 *
 * This function creates a new linked list, applying the given transformation
 * function to each element's data in the original list and storing the result
 * in the new list.
 *
 * @param[in] list Pointer to the linked list to map.
 * @param[in] func Transformation function to apply to each element's data.
 * @param[in] free_data Function to free the data in the new list. if set to
 * NULL, the new created list will use the same free_data function.
 * @return A new linked list with transformed elements.
 */
LinkedList *map(LinkedList *list, void *(*func)(void *),
                void (*free_data)(void *))
{
    LinkedList *new_list =
        init_linked_list(free_data ? free_data : list->free_data);
    if (!new_list)
        return NULL;

    Node *current = list->head;
    while (current != NULL)
    {
        void *new_data = func(current->data);
        append(new_list, new_data);
        current = current->next;
    }

    return new_list;
}

/**
 * @brief Create a new list containing elements that satisfy a condition.
 *
 * This function creates a new linked list containing only the elements from
 * the original list that satisfy the condition specified by the `predicate`
 * function.
 *
 * @param[in] list Pointer to the linked list to filter.
 * @param[in] predicate Function that returns 1 if an element should be
 * included, 0 otherwise.
 * @return A new linked list with filtered elements (copied).
 */
LinkedList *filter(LinkedList *list, int (*predicate)(void *))
{
    LinkedList *new_list = init_linked_list(list->free_data);
    if (!new_list)
        return NULL;

    Node *current = list->head;
    while (current != NULL)
    {
        if (predicate(current->data))
        {
            void *new_data = malloc(sizeof(*(current->data)));
            if (new_data)
            {
                memcpy(new_data, current->data, sizeof(*(current->data)));
                append(new_list, new_data);
            }
        }
        current = current->next;
    }

    return new_list;
}

static Node *merge(Node *left, Node *right,
                   int (*cmp)(const void *, const void *));
static Node *merge_sort(Node *head, int (*cmp)(const void *, const void *));
static Node *split_list(Node *head);

/**
 * @brief Sort the linked list in place using the merge sort algorithm.
 *
 * This function sorts the linked list in place by modifying the links
 * between nodes. It uses the merge sort algorithm for optimal efficiency on
 * linked lists.
 *
 * @param[in] list Pointer to the linked list to sort.
 * @param[in] cmp Comparison function that returns <0, 0, or >0 based on
 * element comparison.
 */
void sort(LinkedList *list, int (*cmp)(const void *, const void *))
{
    if (!list || !list->head || list->size < 2)
        return;
    list->head = merge_sort(list->head, cmp);
}

// Fonction de tri fusion pour les listes chaînées
static Node *merge_sort(Node *head, int (*cmp)(const void *, const void *))
{
    // Cas de base : liste vide ou liste avec un seul élément
    if (!head || !head->next)
        return head;

    // Diviser la liste en deux sous-listes
    Node *middle = split_list(head);
    Node *left = head;
    Node *right = middle;

    // Trier chaque moitié
    left = merge_sort(left, cmp);
    right = merge_sort(right, cmp);

    // Fusionner les deux moitiés triées
    return merge(left, right, cmp);
}

// Fonction pour diviser la liste en deux à partir du milieu
static Node *split_list(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;

    // Utiliser deux pointeurs pour trouver le milieu
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *middle = slow->next;
    slow->next = NULL; // Séparer la liste en deux
    return middle;
}

// Fonction pour fusionner deux sous-listes triées
static Node *merge(Node *left, Node *right,
                   int (*cmp)(const void *, const void *))
{
    // Liste temporaire pour le résultat
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    // Fusionner les deux listes
    while (left && right)
    {
        if (cmp(left->data, right->data) <= 0)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    // Ajouter les éléments restants
    tail->next = left ? left : right;

    return dummy.next;
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
