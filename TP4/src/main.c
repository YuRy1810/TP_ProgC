
#include "fichier.h"
#include "liste.h"
#include "operator.h"

#include <stdio.h>
#include <string.h>

static int exercice_operateurs(void)
{
    int num1;
    int num2;
    int resultat;
    char operateur;

    printf("Entrez num1, num2 et l'operateur : ");
    if (scanf("%d %d %c", &num1, &num2, &operateur) != 3
        || !calculer(num1, num2, operateur, &resultat)) {
        fprintf(stderr, "Saisie ou operation invalide.\n");
        return 0;
    }
    printf("Resultat : %d\n", resultat);
    return 1;
}

static int exercice_fichiers(void)
{
    char nom[256];
    char message[512];
    int choix;

    printf("1. Lire un fichier\n2. Ecrire dans un fichier\nVotre choix : ");
    if (scanf("%d", &choix) != 1) {
        return 0;
    }
    printf("Nom du fichier : ");
    if (scanf(" %255[^\n]", nom) != 1) {
        return 0;
    }
    if (choix == 1) {
        return lire_fichier(nom);
    }
    if (choix == 2) {
        printf("Message : ");
        if (scanf(" %511[^\n]", message) != 1) {
            return 0;
        }
        return ecrire_dans_fichier(nom, message);
    }
    return 0;
}

static int exercice_liste(void)
{
    struct liste_couleurs liste;
    const struct couleur couleurs[10] = {
        {0xff, 0x00, 0x00}, {0x00, 0xff, 0x00},
        {0x00, 0x00, 0xff}, {0xff, 0xff, 0x00},
        {0xff, 0x00, 0xff}, {0x00, 0xff, 0xff},
        {0xff, 0xff, 0xff}, {0x00, 0x00, 0x00},
        {0x80, 0x80, 0x80}, {0xff, 0x80, 0x00}
    };

    init_liste(&liste);
    for (size_t i = 0; i < 10; ++i) {
        if (!insertion(&couleurs[i], &liste)) {
            liberer_liste(&liste);
            return 0;
        }
    }
    parcours(&liste);
    liberer_liste(&liste);
    return 1;
}

int main(void)
{
    int exercice;

    printf("Choisissez l'exercice (1 operateurs, 2 fichiers, 7 liste) : ");
    if (scanf("%d", &exercice) != 1) {
        return 1;
    }
    if (exercice == 1) {
        return exercice_operateurs() ? 0 : 1;
    }
    if (exercice == 2) {
        return exercice_fichiers() ? 0 : 1;
    }
    if (exercice == 7) {
        return exercice_liste() ? 0 : 1;
    }
    fprintf(stderr, "Exercice invalide.\n");
    return 1;
}
