#include <stdint.h>
#include <stdio.h>

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

int main(void)
{
    const struct couleur couleur = {0xef, 0x78, 0x12, 0xff};

    printf("R=%u, G=%u, B=%u, A=%u\n",
           couleur.rouge, couleur.vert, couleur.bleu, couleur.alpha);
    return 0;
}