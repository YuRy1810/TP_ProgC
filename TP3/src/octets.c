#include <stdio.h>

static void afficher_octets(const void *valeur, size_t taille)
{
    const unsigned char *octets = valeur;

    for (size_t i = 0; i < taille; ++i) {
        printf("%02x%s", octets[i], i + 1 == taille ? "\n" : " ");
    }
}

int main(void)
{
    short court = 0x0302;
    int entier = 0x04030201;
    long int grand = 0x0807060504030201L;
    float reel = 1.0f;
    double precis = 1.0;
    long double tres_precis = 1.0L;

    printf("Octets de short :\n");
    afficher_octets(&court, sizeof court);
    printf("Octets de int :\n");
    afficher_octets(&entier, sizeof entier);
    printf("Octets de long int :\n");
    afficher_octets(&grand, sizeof grand);
    printf("Octets de float :\n");
    afficher_octets(&reel, sizeof reel);
    printf("Octets de double :\n");
    afficher_octets(&precis, sizeof precis);
    printf("Octets de long double :\n");
    afficher_octets(&tres_precis, sizeof tres_precis);
    return 0;
}