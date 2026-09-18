#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste)
{
    liste->tete = NULL;
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
    struct noeud_couleur *nouveau = malloc(sizeof *nouveau);

    if (nouveau == NULL) {
        return 0;
    }
    nouveau->valeur = *couleur;
    nouveau->suivant = liste->tete;
    liste->tete = nouveau;
    return 1;
}

void parcours(const struct liste_couleurs *liste)
{
    for (const struct noeud_couleur *noeud = liste->tete;
         noeud != NULL; noeud = noeud->suivant) {
        printf("R=%02x, G=%02x, B=%02x\n",
               noeud->valeur.rouge, noeud->valeur.vert, noeud->valeur.bleu);
    }
}

void liberer_liste(struct liste_couleurs *liste)
{
    while (liste->tete != NULL) {
        struct noeud_couleur *suivant = liste->tete->suivant;
        free(liste->tete);
        liste->tete = suivant;
    }
}