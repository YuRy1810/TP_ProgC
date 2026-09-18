#include <stdio.h>

int main(void) {
    int num1 = 16;
    int num2 = 3;
    char op = '+';
    int resultat;

    switch (op) {
        case '+':
            resultat = num1 + num2;
            break;

        case '-':
            resultat = num1 - num2;
            break;

        case '*':
            resultat = num1 * num2;
            break;

        case '/':
            if (num2 == 0) {
                printf("Division par zero impossible.\n");
                return 1;
            }
            resultat = num1 / num2;
            break;

        case '%':
            if (num2 == 0) {
                printf("Modulo par zero impossible.\n");
                return 1;
            }
            resultat = num1 % num2;
            break;

        case '&':
            resultat = num1 & num2;
            break;

        case '|':
            resultat = num1 | num2;
            break;

        case '~':
            resultat = ~num1;
            break;

        default:
            printf("Operateur inconnu.\n");
            return 1;
    }

    printf("Resultat : %d\n", resultat);

    return 0;
}
