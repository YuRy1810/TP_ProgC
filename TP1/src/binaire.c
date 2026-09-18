#include <stdio.h>
#include <limits.h>

int main(void) {
    int nombres[] = {0, 4096, 65536, 65535, 1024};

    for (int i = 0; i < 5; i++) {
        int nombre = nombres[i];
        int bits[sizeof(int) * CHAR_BIT];
        int taille = 0;

        printf("%d en binaire : ", nombre);

        // Stocker les restes des divisions par 2.
        // do...while permet aussi de traiter le nombre 0.
        do {
            bits[taille] = nombre % 2;
            nombre = nombre / 2;
            taille++;
        } while (nombre > 0);

        // Afficher les bits du dernier au premier.
        for (int j = taille - 1; j >= 0; j--) {
            printf("%d", bits[j]);
        }

        printf("\n");
    }

    return 0;
}