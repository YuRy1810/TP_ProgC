#include <stdint.h>
#include <stdio.h>

#define TAILLE 100

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

struct couleur_comptee {
    struct couleur valeur;
    size_t occurrences;
};

static int egales(struct couleur a, struct couleur b)
{
    return a.rouge == b.rouge && a.vert == b.vert
        && a.bleu == b.bleu && a.alpha == b.alpha;
}

int main(void)
{
    const struct couleur palette[] = {
        {0xff, 0x23, 0x23, 0x45}, {0xff, 0x00, 0x23, 0x12},
        {0x00, 0xff, 0x00, 0xff}, {0x00, 0x00, 0xff, 0xff}
    };
    struct couleur couleurs[TAILLE];
    struct couleur_comptee distinctes[TAILLE];
    size_t nombre_distinctes = 0;

    for (size_t i = 0; i < TAILLE; ++i) {
        couleurs[i] = palette[i % (sizeof palette / sizeof palette[0])];
    }
    for (size_t i = 0; i < TAILLE; ++i) {
        size_t j = 0;
        while (j < nombre_distinctes && !egales(couleurs[i], distinctes[j].valeur)) {
            ++j;
        }
        if (j == nombre_distinctes) {
            distinctes[j].valeur = couleurs[i];
            distinctes[j].occurrences = 1;
            ++nombre_distinctes;
        } else {
            ++distinctes[j].occurrences;
        }
    }

    for (size_t i = 0; i < nombre_distinctes; ++i) {
        struct couleur c = distinctes[i].valeur;
        printf("%02x %02x %02x %02x : %zu\n",
               c.rouge, c.vert, c.bleu, c.alpha, distinctes[i].occurrences);
    }
    return 0;
}