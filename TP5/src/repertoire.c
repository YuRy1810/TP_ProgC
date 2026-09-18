#define _POSIX_C_SOURCE 200809L
#include "repertoire.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static int chemin_enfant(char *destination, size_t taille,
                         const char *dossier, const char *nom)
{
    int longueur = snprintf(destination, taille, "%s/%s", dossier, nom);
    return longueur >= 0 && (size_t)longueur < taille;
}

int lire_dossier(const char *nom_repertoire)
{
    DIR *dossier = opendir(nom_repertoire);
    struct dirent *entree;

    if (dossier == NULL) {
        perror(nom_repertoire);
        return 0;
    }
    errno = 0;
    while ((entree = readdir(dossier)) != NULL) {
        puts(entree->d_name);
    }
    if (errno != 0) {
        perror("readdir");
        closedir(dossier);
        return 0;
    }
    closedir(dossier);
    return 1;
}

static int lire_recursif(const char *nom_repertoire, unsigned int profondeur)
{
    DIR *dossier = opendir(nom_repertoire);
    struct dirent *entree;

    if (dossier == NULL) {
        perror(nom_repertoire);
        return 0;
    }
    errno = 0;
    while ((entree = readdir(dossier)) != NULL) {
        char chemin[4096];
        struct stat informations;

        if (strcmp(entree->d_name, ".") == 0 ||
            strcmp(entree->d_name, "..") == 0) {
            continue;
        }
        if (!chemin_enfant(chemin, sizeof chemin, nom_repertoire, entree->d_name)) {
            fprintf(stderr, "Chemin trop long : %s/%s\n",
                    nom_repertoire, entree->d_name);
            continue;
        }
        for (unsigned int i = 0; i < profondeur; ++i) {
            fputs("  ", stdout);
        }
        puts(chemin);
        if (stat(chemin, &informations) == 0 && S_ISDIR(informations.st_mode) &&
            !lire_recursif(chemin, profondeur + 1)) {
            closedir(dossier);
            return 0;
        }
    }
    if (errno != 0) {
        perror("readdir");
        closedir(dossier);
        return 0;
    }
    closedir(dossier);
    return 1;
}

int lire_dossier_recursif(const char *nom_repertoire)
{
    return lire_recursif(nom_repertoire, 0);
}

int lire_dossier_iteratif(const char *nom_repertoire)
{
    char **a_visiter = malloc(sizeof *a_visiter);
    size_t capacite = 1;
    size_t debut = 0;
    size_t fin = 1;
    int succes = 1;

    if (a_visiter == NULL) {
        return 0;
    }
    a_visiter[0] = strdup(nom_repertoire);
    if (a_visiter[0] == NULL) {
        free(a_visiter);
        return 0;
    }
    while (debut < fin) {
        char *dossier_courant = a_visiter[debut++];
        DIR *dossier = opendir(dossier_courant);
        struct dirent *entree;

        if (dossier == NULL) {
            perror(dossier_courant);
            free(dossier_courant);
            succes = 0;
            continue;
        }
        while ((entree = readdir(dossier)) != NULL) {
            char chemin[4096];
            struct stat informations;

            if (strcmp(entree->d_name, ".") == 0 ||
                strcmp(entree->d_name, "..") == 0 ||
                !chemin_enfant(chemin, sizeof chemin, dossier_courant, entree->d_name)) {
                continue;
            }
            puts(chemin);
            if (stat(chemin, &informations) == 0 && S_ISDIR(informations.st_mode)) {
                if (fin == capacite) {
                    size_t nouvelle_capacite = capacite * 2;
                    char **nouveau = realloc(a_visiter, nouvelle_capacite * sizeof *nouveau);
                    if (nouveau == NULL) {
                        succes = 0;
                        break;
                    }
                    a_visiter = nouveau;
                    capacite = nouvelle_capacite;
                }
                a_visiter[fin++] = strdup(chemin);
                if (a_visiter[fin - 1] == NULL) {
                    succes = 0;
                    break;
                }
            }
        }
        closedir(dossier);
        free(dossier_courant);
    }
    for (size_t i = debut; i < fin; ++i) {
        free(a_visiter[i]);
    }
    free(a_visiter);
    return succes;
}