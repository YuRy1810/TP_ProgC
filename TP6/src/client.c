#include "client.h"
#include "bmp.h"

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int envoyer_recevoir(int socketfd, const char *message)
{
    char reponse[1024];
    size_t longueur = strlen(message);
    ssize_t lus;

    if (write(socketfd, message, longueur) != (ssize_t)longueur) {
        perror("ecriture");
        return -1;
    }
    lus = read(socketfd, reponse, sizeof reponse - 1);
    if (lus <= 0) {
        perror("lecture");
        return -1;
    }
    reponse[lus] = '\0';
    printf("Reponse : %s\n", reponse);
    return 0;
}

int envoie_recois_message(int socketfd)
{
    char message[1000];
    char json[1024];

    printf("Votre message : ");
    if (fgets(message, sizeof message, stdin) == NULL) return -1;
    message[strcspn(message, "\n")] = '\0';
    snprintf(json, sizeof json, "{\"code\":\"message\",\"valeurs\":[\"%.990s\"]}", message);
    return envoyer_recevoir(socketfd, json);
}

int envoie_couleurs(int socketfd, const char *pathname, size_t nombre)
{
    couleur_compteur *compteur = analyse_bmp_image((char *)pathname);
    char json[1024] = "{\"code\":\"couleurs\",\"nombre\":";
    size_t limite;

    if (compteur == NULL) return -1;
    limite = compteur->size < (int)nombre ? (size_t)compteur->size : nombre;
    snprintf(json + strlen(json), sizeof json - strlen(json), "%zu", limite);
    strcat(json, ",\"valeurs\":[");
    for (size_t i = 0; i < limite; ++i) {
        char couleur[16];
        if (compteur->compte_bit == BITS24) {
            couleur24 c = compteur->cc.cc24[i].c;
            snprintf(couleur, sizeof couleur, "\"#%02x%02x%02x\"",
                     c.rouge, c.vert, c.bleu);
        } else {
            couleur32 c = compteur->cc.cc32[i].c;
            snprintf(couleur, sizeof couleur, "\"#%02x%02x%02x\"",
                     c.rouge, c.vert, c.bleu);
        }
        if (i > 0) strcat(json, ",");
        strcat(json, couleur);
    }
    strcat(json, "]}");
    free(compteur->compte_bit == BITS24 ? (void *)compteur->cc.cc24 :
         (void *)compteur->cc.cc32);
    free(compteur);
    return envoyer_recevoir(socketfd, json);
}

int main(int argc, char **argv)
{
    struct sockaddr_in adresse;
    int socketfd;
    long nombre = 10;
    char *fin;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s image.bmp [nombre_de_couleurs 1..30]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 3) {
        nombre = strtol(argv[2], &fin, 10);
        if (*fin != '\0' || nombre < 1 || nombre > 30) {
            fprintf(stderr, "Le nombre de couleurs doit etre compris entre 1 et 30.\n");
            return EXIT_FAILURE;
        }
    }
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) { perror("socket"); return EXIT_FAILURE; }
    memset(&adresse, 0, sizeof adresse);
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(PORT);
    adresse.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(socketfd, (struct sockaddr *)&adresse, sizeof adresse) < 0) {
        perror("connexion serveur");
        close(socketfd);
        return EXIT_FAILURE;
    }
    if (envoie_couleurs(socketfd, argv[1], (size_t)nombre) < 0) {
        close(socketfd);
        return EXIT_FAILURE;
    }
    close(socketfd);
    return EXIT_SUCCESS;
}
