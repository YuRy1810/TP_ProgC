#include <stdio.h>

#define TAILLE 100

int main(void)
{
    int tableau[TAILLE];
    int recherche;
    int gauche = 0;
    int droite = TAILLE - 1;
    int trouve = 0;

    for (int i = 0; i < TAILLE; ++i) {
        tableau[i] = i * 2 - 50;
        printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &recherche) != 1) {
        fprintf(stderr, "Entree invalide.\n");
        return 1;
    }

    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;
        if (tableau[milieu] == recherche) {
            trouve = 1;
            break;
        }
        if (tableau[milieu] < recherche) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }

    printf("Resultat : entier %s\n", trouve ? "present" : "absent");
    return 0;
}