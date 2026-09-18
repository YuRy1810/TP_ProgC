#include <stdio.h>
#include <string.h>

static size_t occurrences(const char *ligne, const char *recherche)
{
    size_t nombre = 0;
    size_t longueur = strlen(recherche);

    if (longueur == 0) {
        return 0;
    }
    for (const char *position = ligne; *position != '\0'; ++position) {
        if (strncmp(position, recherche, longueur) == 0) {
            ++nombre;
        }
    }
    return nombre;
}

int main(int argc, char **argv)
{
    char recherche[256];
    char ligne[1024];
    const char *nom_fichier;
    FILE *fichier;
    unsigned int numero_ligne = 0;
    int resultat = 0;

    if (argc == 2) {
        nom_fichier = argv[1];
    } else if (argc == 1) {
        static char nom_saisi[256];
        printf("Nom du fichier : ");
        if (fgets(nom_saisi, sizeof nom_saisi, stdin) == NULL) {
            return 1;
        }
        nom_saisi[strcspn(nom_saisi, "\n")] = '\0';
        nom_fichier = nom_saisi;
    } else {
        fprintf(stderr, "Usage: %s [fichier]\n", argv[0]);
        return 1;
    }

    printf("Entrez la phrase a rechercher : ");
    if (fgets(recherche, sizeof recherche, stdin) == NULL) {
        return 1;
    }
    recherche[strcspn(recherche, "\n")] = '\0';
    fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror(nom_fichier);
        return 1;
    }
    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        size_t nombre;
        ++numero_ligne;
        nombre = occurrences(ligne, recherche);
        if (nombre > 0) {
            printf("Ligne %u, %zu fois\n", numero_ligne, nombre);
            resultat = 1;
        }
    }
    fclose(fichier);
    if (resultat == 0) {
        printf("Phrase non trouvee.\n");
    }
    return 0;
}