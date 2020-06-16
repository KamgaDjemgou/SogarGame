#ifndef CONNEXIONTCP_H
#define CONNEXIONTCP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 4424
#define TAILLE 1024
#define TAILLE_GRILLE 6
#define IP_SERVEUR "127.0.0.1"
#define QUIT ":exit"
#define REPLAY "REPLAY"


typedef struct _SERVEUR
{
    int socketServer;
    char grille[TAILLE];

}Serveur;
Serveur* serveur;
const char* TIMING;

void initServeur();
void destroyServeur();
void loopServeur();
void startServeur(const char* timing);

int connexionServeur(int clientSocket);
int envoyerMessage(int socket, const char* message);
int recevoirMessage(int socket, char* message);
void generateGrille(char* message);
#endif // CONNEXIONTCP_H
