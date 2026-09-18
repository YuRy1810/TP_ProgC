#include "fichier.h"

#include <stdio.h>

int lire_fichier(const char *nom_de_fichier)
{
    char ligne[512];
    FILE *fichier = fopen(nom_de_fichier, "r");

    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 0;
    }
    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        fputs(ligne, stdout);
    }
    if (ferror(fichier) != 0) {
        fclose(fichier);
        return 0;
    }
    fclose(fichier);
    return 1;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
    FILE *fichier = fopen(nom_de_fichier, "a");

    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 0;
    }
    if (fprintf(fichier, "%s\n", message) < 0) {
        fclose(fichier);
        return 0;
    }
    fclose(fichier);
    return 1;
}