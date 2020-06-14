#ifndef CONNEXIONTCP_H
#define CONNEXIONTCP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4424
#define TAILLE 1024
#define IP_SERVEUR "127.0.0.1"
#define QUIT ":exit"


int connexionServeur(int* clientSocket);
int envoyerMessage(int socket, const char* message);
int recevoirMessage(int socket, char* message);

#endif // CONNEXIONTCP_H
