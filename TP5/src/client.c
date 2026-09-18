/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
static int envoyer_ligne(int socketfd, const char *message)
{
    size_t longueur = strlen(message);
    char reponse[1024];
    ssize_t lus;

    if (write(socketfd, message, longueur) != (ssize_t)longueur ||
        write(socketfd, "\n", 1) != 1) {
        perror("Erreur d'ecriture");
        return -1;
    }
    lus = read(socketfd, reponse, sizeof reponse - 1);
    if (lus <= 0) {
        if (lus < 0) perror("Erreur de lecture");
        return -1;
    }
    reponse[lus] = '\0';
    printf("Message recu : %s", reponse);
    if (reponse[lus - 1] != '\n') putchar('\n');
    return 0;
}

int envoie_recois_message(int socketfd)
{
    char message[1024];

    printf("Votre message (max 1000 caracteres, 'quit' pour sortir) : ");
    if (fgets(message, sizeof message, stdin) == NULL) return -1;
    message[strcspn(message, "\n")] = '\0';
    if (strcmp(message, "quit") == 0) return 1;
    char data[1024];
    snprintf(data, sizeof data, "message: %.1014s", message);
    return envoyer_ligne(socketfd, data);
}

int envoie_operateur_numeros(int socketfd, char operateur,
                             double premier, double deuxieme)
{
    char message[128];
    snprintf(message, sizeof message, "calcule : %c %.17g %.17g",
             operateur, premier, deuxieme);
    return envoyer_ligne(socketfd, message);
}

int main(void)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    if (socketfd < 0) { perror("socket"); return 1; }
    signal(SIGPIPE, SIG_IGN);
    memset(&server_addr, 0, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof server_addr) < 0) {
        perror("connexion serveur");
        close(socketfd);
        return 1;
    }

    for (;;) {
        char choix[32];
        printf("Commande (message/calcul/quit) : ");
        if (fgets(choix, sizeof choix, stdin) == NULL ||
            strncmp(choix, "quit", 4) == 0) break;
        if (strncmp(choix, "calcul", 6) == 0) {
            char operateur;
            double premier;
            double deuxieme = 0;
            printf("Calcul (operateur nombre1 nombre2) : ");
            if (scanf(" %c %lf %lf", &operateur, &premier, &deuxieme) != 3) {
                fprintf(stderr, "Calcul invalide.\n");
                break;
            }
            while (getchar() != '\n') {}
            if (envoie_operateur_numeros(socketfd, operateur, premier, deuxieme) < 0) break;
        } else if (envoie_recois_message(socketfd) < 0) {
            break;
        }
    }
    close(socketfd);
    return 0;
}
