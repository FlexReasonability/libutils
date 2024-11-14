#include <stdio.h>
#include <stdlib.h>

#include "utils.h" // Inclut les déclarations pour Stack et ses fonctions

// Fonction de libération pour des entiers
void free_int(void *data)
{
    free(data);
}

int main()
{
    Stack *stack = init_stack(free_int);
    if (!stack)
    {
        fprintf(stderr, "Erreur d'initialisation de la pile\n");
        return EXIT_FAILURE;
    }

    int *num1 = malloc(sizeof(int));
    int *num2 = malloc(sizeof(int));
    int *num3 = malloc(sizeof(int));
    if (!num1 || !num2 || !num3)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les éléments\n");
        free_stack(stack);
        return EXIT_FAILURE;
    }

    *num1 = 10;
    *num2 = 20;
    *num3 = 30;

    printf("Empilage des éléments : %d, %d, %d\n", *num1, *num2, *num3);
    push(stack, num1);
    push(stack, num2);
    push(stack, num3);

    printf("Taille de la pile après empilage : %zu\n", length(stack));

    int *popped = (int *)pop(stack);
    if (popped)
    {
        printf("Élément dépilé : %d\n", *popped);
        free(popped);
    }
    else
    {
        printf("La pile est vide, rien à dépiler\n");
    }

    printf("Taille de la pile après dépilement : %zu\n", length(stack));
    printf("La pile est-elle vide ? %s\n", is_empty(stack) ? "Oui" : "Non");

    free_stack(stack);
    printf("Pile libérée avec succès.\n");

    return EXIT_SUCCESS;
}
