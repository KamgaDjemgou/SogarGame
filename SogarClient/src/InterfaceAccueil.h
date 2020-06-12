#ifndef INTERFACEACCUEIL_H
#define INTERFACEACCUEIL_H
#include <gtk/gtk.h>

#define  VIEW_ACCUEIL_PATH  "glade/viewAccueil.glade"

typedef struct _InterfaceAccueil
{
	GtkWidget* window;
	GtkWidget* titleGame;
	GtkWidget* pseudoEditor;
	GtkWidget* playButton;
	GtkWidget* quitButton;

}InterfaceAccueil;

InterfaceAccueil* initializeAccueil();
void on_playButton_clicked();
void on_quitButton_clicked();

#endif
