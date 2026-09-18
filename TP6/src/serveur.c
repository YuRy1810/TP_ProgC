#define _POSIX_C_SOURCE 200809L

#include "serveur.h"

#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const char *svg_file_path = "pie_chart.svg";
static int socketfd = -1;
#define PI 3.14159265358979323846

static int envoyer(int client, const char *message)
{
    size_t longueur = strlen(message);
    return write(client, message, longueur) == (ssize_t)longueur ? 0 : -1;
}

static int generer_svg(const char *data)
{
    const char *position = strstr(data, "\"valeurs\"");
    FILE *svg;
    char couleurs[30][8];
    size_t nombre = 0;

    if (position == NULL) {
        return 0;
    }
    while (nombre < 30 && (position = strchr(position, '#')) != NULL) {
        if (sscanf(position, "#%7[0-9a-fA-F]", couleurs[nombre]) != 1 ||
            strlen(couleurs[nombre]) != 6) {
            ++position;
            continue;
        }
        ++nombre;
        position += 7;
    }
    if (nombre == 0 || (svg = fopen(svg_file_path, "w")) == NULL) {
        return 0;
    }
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                 "<svg width=\"500\" height=\"500\" viewBox=\"0 0 500 500\" "
                 "xmlns=\"http://www.w3.org/2000/svg\">\n"
                 "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    for (size_t i = 0; i < nombre; ++i) {
        double debut = -PI / 2.0 + 2.0 * PI * (double)i / (double)nombre;
        double fin = -PI / 2.0 + 2.0 * PI * (double)(i + 1) / (double)nombre;
        double x1 = 250.0 + 200.0 * cos(debut);
        double y1 = 250.0 + 200.0 * sin(debut);
        double x2 = 250.0 + 200.0 * cos(fin);
        double y2 = 250.0 + 200.0 * sin(fin);
        fprintf(svg, "<path d=\"M250,250 L%.2f,%.2f A200,200 0 0,1 %.2f,%.2f Z\" "
                     "fill=\"#%s\"/>\n", x1, y1, x2, y2, couleurs[i]);
    }
    fputs("</svg>\n", svg);
    fclose(svg);
    return 1;
}

int recois_envoie_message(int client, char data[1024])
{
    if (strncmp(data, "{\"code\":\"message\"", 17) == 0) {
        return envoyer(client, data);
    }
    if (strncmp(data, "{\"code\":\"couleurs\"", 18) == 0) {
        return generer_svg(data) ? envoyer(client, "{\"ok\":true}\n") : -1;
    }
    return envoyer(client, "{\"ok\":false,\"erreur\":\"requete invalide\"}\n");
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
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);
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
    puts("Serveur en attente de connexions...");
    for (;;) {
        int client = accept(socketfd, NULL, NULL);
        char data[1024] = {0};
        ssize_t lus;
        if (client < 0) continue;
        lus = read(client, data, sizeof data - 1);
        if (lus > 0) {
            data[lus] = '\0';
            recois_envoie_message(client, data);
        }
        close(client);
    }
}
