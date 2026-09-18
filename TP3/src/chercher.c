#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void)
{
    int tableau[TAILLE];
    int recherche;
    int trouve = 0;

    srand((unsigned int)time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        tableau[i] = rand() % 2001 - 1000;
        printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &recherche) != 1) {
        fprintf(stderr, "Entree invalide.\n");
        return 1;
    }

    for (int i = 0; i < TAILLE; ++i) {
        if (tableau[i] == recherche) {
            trouve = 1;
            break;
        }
    }
    printf("Resultat : entier %s\n", trouve ? "present" : "absent");
    return 0;
}