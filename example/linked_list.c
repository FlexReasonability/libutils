#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

void free_string(void *data)
{
    free(data);
}

void print_element(void *data)
{
    printf("%s\n", (char *)data);
}

void *to_upper(void *data)
{
    char *str = (char *)data;
    char *result = malloc(strlen(str) + 1);
    for (size_t i = 0; i < strlen(str); i++)
    {
        result[i] = toupper(str[i]);
    }
    result[strlen(str)] = '\0';
    return result;
}

int longer_than_3(void *data)
{
    return strlen((char *)data) > 3;
}

int compare_strings(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

int main()
{
    LinkedList *list = init_linked_list(free_string);

    append(list, strdup("apple"));
    append(list, strdup("banana"));
    append(list, strdup("pear"));
    insert_at(list, strdup("grape"), 1);

    printf("Liste initiale:\n");
    foreach(list, print_element);

    char *second_element = (char *)get_at(list, 1);
    printf("\nÉlément à la position 1 : %s\n", second_element);

    LinkedList *filtered_list = filter(list, longer_than_3);
    printf("\nListe filtrée (longueur > 3) :\n");
    foreach(filtered_list, print_element);

    LinkedList *upper_list = map(list, to_upper, free_string);
    printf("\nListe en majuscules :\n");
    foreach(upper_list, print_element);

    sort(list, compare_strings);
    printf("\nListe triée :\n");
    foreach(list, print_element);

    free_linked_list(list);
    free_linked_list(filtered_list);
    free_linked_list(upper_list);

    return 0;
}
