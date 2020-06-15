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
#include <pthread.h>
#include <unistd.h>

#include "Joueur.h"

#define PORT 4424
#define TAILLE 1024
#define TAILLE_GRILLE 6
#define IP_SERVEUR "127.0.0.1"
#define QUIT ":exit"
#define NBRE_JOUEURS 2


typedef struct _SERVEUR
{
    int socketServer;
    Joueur joueur1;
    Joueur joueur2;
    int tour;
    char grille[TAILLE];

}Serveur;
Serveur* serveur;

void initServeur();
void destroyServeur();
void loopServeur();
void startServeur();
void traiterFinTour();

int connexionServeur(int clientSocket);
void connexionJoueurs();
int envoyerMessage(int socket, const char* message);
int recevoirMessage(int socket, char* message);
void* comminicateWithSecond(void*);
void generateGrille(char* message);
#endif // CONNEXIONTCP_H
