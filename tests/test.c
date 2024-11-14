#include <stdio.h>

#include "test_linked_list.h"
#include "test_stack.h"

int main()
{
    int total_tests = 9;
    int passed_tests = 0;

    printf("\nRunning tests for linked list...\n");
    passed_tests += test_list_initialization();
    passed_tests += test_append_elements();
    passed_tests += test_insert_at_position();
    passed_tests += test_remove_at_position();
    passed_tests += test_get_at_invalid_index();
    passed_tests += test_foreach();
    passed_tests += test_map();
    passed_tests += test_filter();
    passed_tests += test_sort();
    printf("\n%d/%d tests passed.\n", passed_tests, total_tests);

    total_tests = 6;
    passed_tests = 0;
    printf("\nRunning tests for stack...\n");
    passed_tests += test_stack_initialization();
    passed_tests += test_push_elements();
    passed_tests += test_pop_elements();
    passed_tests += test_pop_empty_stack();
    passed_tests += test_is_empty();
    passed_tests += test_stack_length();
    printf("\n%d/%d tests passed.\n", passed_tests, total_tests);

    return 0;
}