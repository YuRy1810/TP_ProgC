#define _POSIX_C_SOURCE 200809L

#include "serveur.h"

#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int socketfd = -1;

static int envoyer_ligne(int client_socket_fd, const char *message)
{
    size_t longueur = strlen(message);

    if (write(client_socket_fd, message, longueur) != (ssize_t)longueur ||
        write(client_socket_fd, "\n", 1) != 1) {
        perror("Erreur d'ecriture");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int renvoie_message(int client_socket_fd, char *data)
{
    return envoyer_ligne(client_socket_fd, data);
}

int recois_numeros_calcule(int client_socket_fd, const char *data)
{
    char operateur;
    double premier;
    double deuxieme;
    double resultat;

    if (sscanf(data, "calcule : %c %lf %lf", &operateur,
               &premier, &deuxieme) != 3) {
        return envoyer_ligne(client_socket_fd, "calcule : requete invalide");
    }
    switch (operateur) {
    case '+': resultat = premier + deuxieme; break;
    case '-': resultat = premier - deuxieme; break;
    case '*': resultat = premier * deuxieme; break;
    case '/':
        if (deuxieme == 0.0) return envoyer_ligne(client_socket_fd, "calcule : division par zero");
        resultat = premier / deuxieme;
        break;
    default:
        return envoyer_ligne(client_socket_fd, "calcule : operateur invalide");
    }
    char reponse[128];
    snprintf(reponse, sizeof reponse, "calcule : %.17g", resultat);
    return envoyer_ligne(client_socket_fd, reponse);
}

static void traiter_message(int client_socket_fd, char *data)
{
    data[strcspn(data, "\r\n")] = '\0';
    printf("Message recu : %s\n", data);
    if (strncmp(data, "calcule :", 9) == 0) {
        recois_numeros_calcule(client_socket_fd, data);
    } else if (strncmp(data, "message:", 8) == 0) {
        renvoie_message(client_socket_fd, data);
    } else {
        envoyer_ligne(client_socket_fd, "Commande inconnue");
    }
}

static void gerer_client(int client_socket_fd)
{
    char data[1024];
    size_t position = 0;

    for (;;) {
        char caractere;
        ssize_t lus = read(client_socket_fd, &caractere, 1);
        if (lus == 0) break;
        if (lus < 0) {
            if (errno == EINTR) continue;
            perror("Erreur de lecture");
            break;
        }
        if (caractere == '\n') {
            data[position] = '\0';
            traiter_message(client_socket_fd, data);
            position = 0;
        } else if (position + 1 < sizeof data) {
            data[position++] = caractere;
        }
    }
    close(client_socket_fd);
}

static void gestionnaire_ctrl_c(int signal_recu)
{
    (void)signal_recu;
    if (socketfd >= 0) close(socketfd);
    _exit(EXIT_SUCCESS);
}

int main(void)
{
    struct sockaddr_in adresse;
    int option = 1;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) { perror("socket"); return EXIT_FAILURE; }
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option) < 0) {
        perror("setsockopt");
        close(socketfd);
        return EXIT_FAILURE;
    }
    memset(&adresse, 0, sizeof adresse);
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(PORT);
    adresse.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(socketfd, (struct sockaddr *)&adresse, sizeof adresse) < 0 ||
        listen(socketfd, 10) < 0) {
        perror("bind/listen");
        close(socketfd);
        return EXIT_FAILURE;
    }
    signal(SIGINT, gestionnaire_ctrl_c);
    signal(SIGCHLD, SIG_IGN);
    puts("Serveur en attente de connexions...");
    for (;;) {
        int client = accept(socketfd, NULL, NULL);
        if (client < 0) {
            if (errno == EINTR) continue;
            perror("accept");
            continue;
        }
        pid_t enfant = fork();
        if (enfant == 0) {
            close(socketfd);
            gerer_client(client);
            _exit(EXIT_SUCCESS);
        }
        if (enfant < 0) perror("fork");
        close(client);
    }
}
