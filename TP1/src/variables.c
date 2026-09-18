#include <stdio.h>

int main(void) {
    char lettre = 'A';
    signed char petit = -10;
    unsigned char petit_positif = 200;

    signed short court = -100;
    unsigned short court_positif = 100;

    signed int entier = -1000;
    unsigned int entier_positif = 1000;

    signed long int grand = -10000L;
    unsigned long int grand_positif = 10000UL;

    signed long long int tres_grand = -100000LL;
    unsigned long long int tres_grand_positif = 100000ULL;

    float decimal = 1.5f;
    double precis = 3.14159;
    long double tres_precis = 2.71828L;

    printf("char : %c\n", lettre);
    printf("signed char : %hhd\n", petit);
    printf("unsigned char : %hhu\n", petit_positif);

    printf("signed short : %hd\n", court);
    printf("unsigned short : %hu\n", court_positif);

    printf("signed int : %d\n", entier);
    printf("unsigned int : %u\n", entier_positif);

    printf("signed long int : %ld\n", grand);
    printf("unsigned long int : %lu\n", grand_positif);

    printf("signed long long int : %lld\n", tres_grand);
    printf("unsigned long long int : %llu\n", tres_grand_positif);

    printf("float : %.2f\n", decimal);
    printf("double : %.5f\n", precis);
    printf("long double : %.5Lf\n", tres_precis);

    return 0;
}