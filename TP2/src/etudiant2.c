#include <stdio.h>
#include <string.h>

struct etudiant {
    char nom[32];
    char prenom[32];
    char adresse[80];
    float note_programmation;
    float note_systeme;
};

int main(void)
{
    struct etudiant etudiants[5];
    const char *noms[] = {"Dupont", "Martin", "Bernard", "Petit", "Robert"};
    const char *prenoms[] = {"Marie", "Pierre", "Sofia", "Lucas", "Emma"};
    const char *adresses[] = {
        "20, Boulevard Niels Bohr, Lyon",
        "22, Boulevard Niels Bohr, Lyon",
        "5, rue des Lilas, Grenoble",
        "10, avenue Victor Hugo, Paris",
        "8, rue Pasteur, Lille"
    };
    const float notes_c[] = {16.5f, 14.0f, 15.5f, 12.0f, 17.0f};
    const float notes_systeme[] = {12.1f, 14.1f, 13.5f, 15.0f, 16.0f};

    for (size_t i = 0; i < 5; ++i) {
        strcpy(etudiants[i].nom, noms[i]);
        strcpy(etudiants[i].prenom, prenoms[i]);
        strcpy(etudiants[i].adresse, adresses[i]);
        etudiants[i].note_programmation = notes_c[i];
        etudiants[i].note_systeme = notes_systeme[i];
    }

    for (size_t i = 0; i < 5; ++i) {
        printf("Etudiant %zu :\n", i + 1);
        printf("  Nom : %s\n  Prenom : %s\n  Adresse : %s\n",
               etudiants[i].nom, etudiants[i].prenom, etudiants[i].adresse);
        printf("  Note 1 : %.1f\n  Note 2 : %.1f\n\n",
               etudiants[i].note_programmation, etudiants[i].note_systeme);
    }

    return 0;
}