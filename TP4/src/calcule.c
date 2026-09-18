#include "operator.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char operateur;
    char *fin_numero;
    long premier;
    long deuxieme;
    int resultat;

    if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0') {
        fprintf(stderr, "Usage: %s <operateur> <nombre1> <nombre2>\n", argv[0]);
        return 1;
    }
    operateur = argv[1][0];
    premier = strtol(argv[2], &fin_numero, 10);
    if (*fin_numero != '\0') {
        fprintf(stderr, "Premier nombre invalide.\n");
        return 1;
    }
    deuxieme = strtol(argv[3], &fin_numero, 10);
    if (*fin_numero != '\0') {
        fprintf(stderr, "Deuxieme nombre invalide.\n");
        return 1;
    }
    if (!calculer((int)premier, (int)deuxieme, operateur, &resultat)) {
        fprintf(stderr, "Operation invalide ou division par zero.\n");
        return 1;
    }
    printf("Resultat : %d\n", resultat);
    return 0;
}