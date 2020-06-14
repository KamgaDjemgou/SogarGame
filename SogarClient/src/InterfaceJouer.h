#ifndef INTERFACEJOUER_H
#define INTERFACEJOUER_H
#include <gtk/gtk.h>

#define  VIEW_JOUER_PATH  "glade/viewJouer.glade"
#define TAILLE_GRILLE 6

typedef struct _InterfaceJouer
{
	GtkWidget* window;
	GtkWidget* grille;
	GtkWidget*  imagesBoutons[TAILLE_GRILLE][TAILLE_GRILLE];
	GString imagesPaths[TAILLE_GRILLE][TAILLE_GRILLE];
	GtkWidget* tempsLabel;
	GtkWidget* tempsValeur;
	GtkWidget* monPseudo;
	GtkWidget* monScore;
	GtkWidget* pseudoAdv;
	GtkWidget* scoreAdv;

}InterfaceJouer;

InterfaceJouer* initializeJouer();
void insertImages(InterfaceJouer* ihmJouer);

#endif
