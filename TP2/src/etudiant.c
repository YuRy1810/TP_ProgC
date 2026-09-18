#include <stdio.h>

int main(void)
{
    const char *noms[] = {"Dupont", "Martin", "Bernard", "Petit", "Robert"};
    const char *prenoms[] = {"Marie", "Pierre", "Sofia", "Lucas", "Emma"};
    const char *adresses[] = {
        "20, Boulevard Niels Bohr, Lyon",
        "22, Boulevard Niels Bohr, Lyon",
        "5, rue des Lilas, Grenoble",
        "10, avenue Victor Hugo, Paris",
        "8, rue Pasteur, Lille"
    };
    const float notes_programmation[] = {16.5f, 14.0f, 15.5f, 12.0f, 17.0f};
    const float notes_systeme[] = {12.1f, 14.1f, 13.5f, 15.0f, 16.0f};
    const size_t nombre_etudiants = sizeof noms / sizeof noms[0];

    for (size_t i = 0; i < nombre_etudiants; ++i) {
        printf("Etudiant %zu :\n", i + 1);
        printf("  Nom : %s\n", noms[i]);
        printf("  Prenom : %s\n", prenoms[i]);
        printf("  Adresse : %s\n", adresses[i]);
        printf("  Programmation en C : %.1f\n", notes_programmation[i]);
        printf("  Systeme d'exploitation : %.1f\n\n", notes_systeme[i]);
    }

    return 0;
}