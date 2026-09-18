#include <stdio.h>

unsigned long long factorielle(unsigned int nombre)
{
    if (nombre == 0) {
        return 1;
    }
    return nombre * factorielle(nombre - 1);
}

int main(void)
{
    unsigned int nombre;

    printf("Entrez un entier naturel (0 a 20) : ");
    if (scanf("%u", &nombre) != 1 || nombre > 20) {
        fprintf(stderr, "Valeur invalide : choisissez un entier entre 0 et 20.\n");
        return 1;
    }
    printf("%u! = %llu\n", nombre, factorielle(nombre));
    return 0;
}