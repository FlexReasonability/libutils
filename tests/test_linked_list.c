#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"

void free_int(void *data)
{
    free(data);
}

void print_test_result(const char *test_name, int passed)
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

int main()
{
    int total_tests = 4;
    int passed_tests = 0;

    printf("\nRunning tests for linked list...\n");

    passed_tests += test_list_initialization();
    passed_tests += test_append_elements();
    passed_tests += test_insert_at_position();
    passed_tests += test_remove_at_position();

    printf("\n%d/%d tests passed.\n", passed_tests, total_tests);
    return passed_tests == total_tests ? 0 : 1;
}
