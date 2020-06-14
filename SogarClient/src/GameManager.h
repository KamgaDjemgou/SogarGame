#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InterfaceAccueil.h"
#include "InterfaceJouer.h"
#include "ConnexionTCP.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct _GameManager
{
	InterfaceAccueil* pageAccueil;
	InterfaceJouer*  pageJouer;
	GtkWidget* dialog;
	int socket;
	char pseudo[TAILLE];

}GameManager;
GameManager* gameManager;

void initGTK();
void initGameManager();
void initStyle();
void on_playButton_clicked();
void on_quit();
void startGame();
void afficherErreur(GtkWidget* parent, const char* message);
void* communicateWithServer(void* arg);

#endif
