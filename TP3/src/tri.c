#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

static void afficher(const int *tableau)
{
    for (int i = 0; i < TAILLE; ++i) {
        printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
    }
}

int main(void)
{
    int tableau[TAILLE];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        tableau[i] = rand() % 2001 - 1000;
    }

    printf("Tableau non trie :\n");
    afficher(tableau);

    for (int i = 1; i < TAILLE; ++i) {
        int valeur = tableau[i];
        int j = i - 1;
        while (j >= 0 && tableau[j] > valeur) {
            tableau[j + 1] = tableau[j];
            --j;
        }
        tableau[j + 1] = valeur;
    }

    printf("Tableau trie par ordre croissant :\n");
    afficher(tableau);
    return 0;
}