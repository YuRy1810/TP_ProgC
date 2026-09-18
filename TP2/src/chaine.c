#include <stdio.h>

static unsigned long longueur(const char *chaine)
{
    unsigned long taille = 0;

    while (chaine[taille] != '\0') {
        ++taille;
    }
    return taille;
}

static void copier(char *destination, const char *source)
{
    while (*source != '\0') {
        *destination++ = *source++;
    }
    *destination = '\0';
}

static void concatener(char *destination, const char *source)
{
    while (*destination != '\0') {
        ++destination;
    }
    copier(destination, source);
}

int main(void)
{
    const char premiere[] = "Hello";
    const char deuxieme[] = " World!";
    char copie[sizeof premiere];
    char resultat[sizeof premiere + sizeof deuxieme - 1];

    copier(copie, premiere);
    copier(resultat, premiere);
    concatener(resultat, deuxieme);

    printf("Longueur de \"%s\" : %lu\n", premiere, longueur(premiere));
    printf("Copie : %s\n", copie);
    printf("Concatenation : %s\n", resultat);
    printf("Longueur de la concatenation : %lu\n", longueur(resultat));
    return 0;
}