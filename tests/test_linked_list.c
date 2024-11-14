#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../src/node.h"

struct LinkedList
{
    struct Node *head;
    size_t size;
    void (*free_data)(void *data);
};

// Fonction de libération pour des entiers
static void free_int(void *data)
{
    free(data);
}

// Fonction pour afficher le résultat d'un test
static void print_test_result(const char *test_name, int passed)
{
    if (passed)
    {
        printf("[SUCCESS] %s\n", test_name);
    }
    else
    {
        printf("[FAILURE] %s\n", test_name);
    }
}

// Fonctions utilitaires pour les tests
int *sum_ptr;

void add_1(void *data)
{
    int *int_ptr = (int *)data;
    *int_ptr = *int_ptr + 1;
}

void *double_value(void *data)
{
    int *result = malloc(sizeof(int));
    *result = (*(int *)data) * 2;
    return result;
}

int greater_than_10(void *data)
{
    return *(int *)data > 10;
}

int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Fonctions de test

int test_list_initialization()
{
    LinkedList *list = init_linked_list(free_int);
    int passed = list != NULL && list->size == 0 && list->head == NULL;
    free_linked_list(list);
    print_test_result("test_list_initialization", passed);
    return passed;
}

int test_append_elements()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    append(list, num1);
    append(list, num2);

    int passed = list->size == 2 && *(int *)get_at(list, 0) == 10
        && *(int *)get_at(list, 1) == 20;

    free_linked_list(list);
    print_test_result("test_append_elements", passed);
    return passed;
}

int test_insert_at_position()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    int *num3 = malloc(sizeof(int));
    *num3 = 30;
    append(list, num1);
    append(list, num2);
    insert_at(list, num3, 1);

    int passed = list->size == 3 && *(int *)get_at(list, 1) == 30;

    free_linked_list(list);
    print_test_result("test_insert_at_position", passed);
    return passed;
}

int test_remove_at_position()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    int *num3 = malloc(sizeof(int));
    *num3 = 30;
    append(list, num1);
    append(list, num2);
    append(list, num3);

    remove_at(list, 1);

    int passed = list->size == 2 && *(int *)get_at(list, 1) == 30;

    free_linked_list(list);
    print_test_result("test_remove_at_position", passed);
    return passed;
}

int test_get_at_invalid_index()
{
    LinkedList *list = init_linked_list(free_int);
    int *num = malloc(sizeof(int));
    *num = 10;
    append(list, num);

    int *data = (int *)get_at(list, 1); // Index out of bounds
    int passed = data == NULL;

    free_linked_list(list);
    print_test_result("test_get_at_invalid_index", passed);
    return passed;
}

int test_foreach()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    append(list, num1);
    append(list, num2);

    foreach(list, add_1);

    int passed = *((int *)get_at(list, 0)) + *((int *)get_at(list, 1)) == 32;

    free_linked_list(list);
    print_test_result("test_foreach", passed);
    return passed;
}

int test_map()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    append(list, num1);
    append(list, num2);

    LinkedList *doubled_list = map(list, double_value, free_int);

    int passed = doubled_list->size == 2
        && *(int *)get_at(doubled_list, 0) == 20
        && *(int *)get_at(doubled_list, 1) == 40;

    free_linked_list(list);
    free_linked_list(doubled_list);
    print_test_result("test_map", passed);
    return passed;
}

int test_filter()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 5;
    int *num2 = malloc(sizeof(int));
    *num2 = 15;
    int *num3 = malloc(sizeof(int));
    *num3 = 25;
    append(list, num1);
    append(list, num2);
    append(list, num3);

    LinkedList *filtered_list = filter(list, greater_than_10);

    int passed = filtered_list->size == 2
        && *(int *)get_at(filtered_list, 0) == 15
        && *(int *)get_at(filtered_list, 1) == 25;

    free_linked_list(list);
    free_linked_list(filtered_list);
    print_test_result("test_filter", passed);
    return passed;
}

int test_sort()
{
    LinkedList *list = init_linked_list(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 30;
    int *num2 = malloc(sizeof(int));
    *num2 = 10;
    int *num3 = malloc(sizeof(int));
    *num3 = 20;
    append(list, num1);
    append(list, num2);
    append(list, num3);

    sort(list, compare_ints);

    int passed = list->size == 3 && *(int *)get_at(list, 0) == 10
        && *(int *)get_at(list, 1) == 20 && *(int *)get_at(list, 2) == 30;

    free_linked_list(list);
    print_test_result("test_sort", passed);
    return passed;
}
