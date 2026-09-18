#ifndef LISTE_H
#define LISTE_H

struct couleur {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
};

struct noeud_couleur {
    struct couleur valeur;
    struct noeud_couleur *suivant;
};

struct liste_couleurs {
    struct noeud_couleur *tete;
};

void init_liste(struct liste_couleurs *liste);
int insertion(const struct couleur *couleur, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void liberer_liste(struct liste_couleurs *liste);

#endif