#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InterfaceAccueil.h"
typedef struct _GameManager
{
	InterfaceAccueil* pageAccueil;

}GameManager;
GameManager* gameManager;

void initGTK();
void initGameManager();
void initStyle();
void startGame();

#endif
