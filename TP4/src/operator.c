#include "operator.h"

int somme(int num1, int num2)
{
    return num1 + num2;
}

int difference(int num1, int num2)
{
    return num1 - num2;
}

int produit(int num1, int num2)
{
    return num1 * num2;
}

int quotient(int num1, int num2)
{
    return num1 / num2;
}

int modulo(int num1, int num2)
{
    return num1 % num2;
}

int et_binaire(int num1, int num2)
{
    return num1 & num2;
}

int ou_binaire(int num1, int num2)
{
    return num1 | num2;
}

int negation(int num1)
{
    return ~num1;
}

int calculer(int num1, int num2, char operateur, int *resultat)
{
    if ((operateur == '/' || operateur == '%') && num2 == 0) {
        return 0;
    }

    switch (operateur) {
    case '+': *resultat = somme(num1, num2); break;
    case '-': *resultat = difference(num1, num2); break;
    case '*': *resultat = produit(num1, num2); break;
    case '/': *resultat = quotient(num1, num2); break;
    case '%': *resultat = modulo(num1, num2); break;
    case '&': *resultat = et_binaire(num1, num2); break;
    case '|': *resultat = ou_binaire(num1, num2); break;
    case '~': *resultat = negation(num1); break;
    default: return 0;
    }
    return 1;
}