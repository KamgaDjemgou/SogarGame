#ifndef JOUEUR_H
#define JOUEUR_H

#define TAILLE 1024

typedef struct _Joueur
{
    int socket;
    char pseudo[TAILLE];
    int score;
}Joueur;

#endif // JOUEUR_H
