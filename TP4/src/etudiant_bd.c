#include <stdio.h>

#define NOMBRE_ETUDIANTS 5

struct etudiant {
    char nom[64];
    char prenom[64];
    char adresse[128];
    float note_programmation;
    float note_systeme;
};

int main(void)
{
    struct etudiant etudiants[NOMBRE_ETUDIANTS];
    FILE *fichier = fopen("etudiant.txt", "w");

    if (fichier == NULL) {
        perror("etudiant.txt");
        return 1;
    }
    for (size_t i = 0; i < NOMBRE_ETUDIANTS; ++i) {
        printf("Etudiant %zu\n", i + 1);
        printf("Nom : ");
        if (scanf(" %63[^\n]", etudiants[i].nom) != 1) {
            fclose(fichier);
            return 1;
        }
        printf("Prenom : ");
        if (scanf(" %63[^\n]", etudiants[i].prenom) != 1) {
            fclose(fichier);
            return 1;
        }
        printf("Adresse : ");
        if (scanf(" %127[^\n]", etudiants[i].adresse) != 1) {
            fclose(fichier);
            return 1;
        }
        printf("Note 1 : ");
        if (scanf("%f", &etudiants[i].note_programmation) != 1) {
            fclose(fichier);
            return 1;
        }
        printf("Note 2 : ");
        if (scanf("%f", &etudiants[i].note_systeme) != 1) {
            fclose(fichier);
            return 1;
        }
        if (fprintf(fichier, "%s;%s;%s;%.2f;%.2f\n",
                    etudiants[i].nom, etudiants[i].prenom, etudiants[i].adresse,
                    etudiants[i].note_programmation, etudiants[i].note_systeme) < 0) {
            fclose(fichier);
            return 1;
        }
    }
    fclose(fichier);
    printf("Les etudiants ont ete enregistres dans etudiant.txt.\n");
    return 0;
}