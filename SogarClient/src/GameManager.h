#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InterfaceAccueil.h"
#include "InterfaceJouer.h"

typedef struct _GameManager
{
	InterfaceAccueil* pageAccueil;
	InterfaceJouer*  pageJouer;

}GameManager;
GameManager* gameManager;

void initGTK();
void initGameManager();
void initStyle();
void on_playButton_clicked();
void on_quit();
void startGame();

#endif
