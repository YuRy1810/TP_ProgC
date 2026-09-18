/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef SERVEUR_H
#define SERVEUR_H

#define PORT 8089

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int renvoie_message(int, char *);
int recois_numeros_calcule(int client_socket_fd, const char *data);

#endif
