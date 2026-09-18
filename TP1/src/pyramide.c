#include <stdio.h>

int main(void) {
    int n = 5;
    int i, j;

    for (i = 1; i <= n; i++) {
        // Espaces pour centrer la ligne.
        for (j = 0; j < n - i; j++) {
            printf(" ");
        }

        // Nombres croissants de 1 a i.
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // Nombres decroissants de i-1 a 1.
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        printf("\n");
    }

    printf("Generation de la pyramide terminee.\n");

    return 0;
}
