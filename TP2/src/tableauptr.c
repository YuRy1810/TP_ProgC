#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 10

static void afficher_entiers(const int *tableau)
{
    for (const int *p = tableau; p < tableau + TAILLE; ++p) {
        printf("%d%s", *p, p == tableau + TAILLE - 1 ? "\n" : ", ");
    }
}

static void afficher_reels(const float *tableau)
{
    for (const float *p = tableau; p < tableau + TAILLE; ++p) {
        printf("%.2f%s", *p, p == tableau + TAILLE - 1 ? "\n" : ", ");
    }
}

int main(void)
{
    int entiers[TAILLE];
    float reels[TAILLE];

    srand((unsigned int)time(NULL));
    for (int *pi = entiers, *fin = entiers + TAILLE; pi < fin; ++pi) {
        *pi = rand() % 100;
    }
    for (float *pf = reels, *fin = reels + TAILLE; pf < fin; ++pf) {
        *pf = (float)rand() / (float)RAND_MAX * 100.0f;
    }

    printf("Tableau d'entiers avant :\n");
    afficher_entiers(entiers);
    printf("Tableau de reels avant :\n");
    afficher_reels(reels);

    for (int *pi = entiers, *fin = entiers + TAILLE; pi < fin; pi += 2) {
        *pi *= 3;
    }
    for (float *pf = reels, *fin = reels + TAILLE; pf < fin; pf += 2) {
        *pf *= 3.0f;
    }

    printf("Tableau d'entiers apres :\n");
    afficher_entiers(entiers);
    printf("Tableau de reels apres :\n");
    afficher_reels(reels);
    return 0;
}