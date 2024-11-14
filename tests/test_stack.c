#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../src/node.h"

// Stack structure definition
struct Stack
{
    struct Node *head;
    size_t size;
    void (*free_data)(void *data);
};

// Function to free integer data in the stack
static void free_int(void *data)
{
    free(data);
}

// Function to print test results
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

// Stack test functions

int test_stack_initialization()
{
    Stack *stack = init_stack(free_int);
    int passed = stack != NULL && stack->size == 0 && stack->head == NULL;
    free_stack(stack);
    print_test_result("test_stack_initialization", passed);
    return passed;
}

int test_push_elements()
{
    Stack *stack = init_stack(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    push(stack, num1);
    push(stack, num2);

    int passed = stack->size == 2 && *((int *)(stack->head->data)) == 20;

    free_stack(stack);
    print_test_result("test_push_elements", passed);
    return passed;
}

int test_pop_elements()
{
    Stack *stack = init_stack(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    push(stack, num1);
    push(stack, num2);

    int *popped_data = (int *)pop(stack);
    int passed = *popped_data == 20 && stack->size == 1;

    free(popped_data);
    free_stack(stack);
    print_test_result("test_pop_elements", passed);
    return passed;
}

int test_pop_empty_stack()
{
    Stack *stack = init_stack(free_int);
    void *popped_data = pop(stack); // Popping from empty stack
    int passed = popped_data == NULL && stack->size == 0;

    free_stack(stack);
    print_test_result("test_pop_empty_stack", passed);
    return passed;
}

int test_is_empty()
{
    Stack *stack = init_stack(free_int);
    int passed = is_empty(stack) == 1;

    int *num = malloc(sizeof(int));
    *num = 10;
    push(stack, num);
    passed = passed && is_empty(stack) == 0;

    free_stack(stack);
    print_test_result("test_is_empty", passed);
    return passed;
}

int test_stack_length()
{
    Stack *stack = init_stack(free_int);
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    push(stack, num1);
    push(stack, num2);

    int passed = length(stack) == 2;

    free_stack(stack);
    print_test_result("test_stack_length", passed);
    return passed;
}
