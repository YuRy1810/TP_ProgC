#include <stdio.h>

int main(void) {
    int compteur = 5;

    if (compteur < 1 || compteur >= 10) {
        printf("La taille doit etre comprise entre 1 et 9.\n");
        return 1;
    }

    printf("Version for :\n");

    for (int ligne = 1; ligne <= compteur; ligne++) {
        for (int colonne = 1; colonne <= ligne; colonne++) {
            if (colonne == 1 || colonne == ligne || ligne == compteur) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    printf("\nVersion while :\n");

    int ligne = 1;

    while (ligne <= compteur) {
        int colonne = 1;

        while (colonne <= ligne) {
            if (colonne == 1 || colonne == ligne || ligne == compteur) {
                printf("* ");
            } else {
                printf("# ");
            }

            colonne++;
        }

        printf("\n");
        ligne++;
    }

    return 0;
}