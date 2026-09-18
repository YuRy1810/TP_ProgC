#include <stdio.h>

static int meme_phrase(const char *premiere, const char *deuxieme)
{
    while (*premiere != '\0' && *deuxieme != '\0') {
        if (*premiere++ != *deuxieme++) {
            return 0;
        }
    }
    return *premiere == '\0' && *deuxieme == '\0';
}

int main(void)
{
    const char *phrases[10] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };
    char recherche[256];
    int trouve = 0;

    printf("Entrez une phrase : ");
    if (fgets(recherche, sizeof recherche, stdin) == NULL) {
        fprintf(stderr, "Lecture impossible.\n");
        return 1;
    }
    char *fin = recherche;
    while (*fin != '\0') {
        if (*fin == '\n') {
            *fin = '\0';
            break;
        }
        ++fin;
    }

    for (size_t i = 0; i < 10; ++i) {
        if (meme_phrase(recherche, phrases[i])) {
            trouve = 1;
            break;
        }
    }
    printf("Phrase %s\n", trouve ? "trouvee" : "non trouvee");
    return 0;
}
