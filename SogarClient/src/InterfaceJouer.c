#include "InterfaceJouer.h"

InterfaceJouer* initializeJouer(){
    InterfaceJouer *ihmJouer;
	GtkBuilder *builder;


	ihmJouer = (InterfaceJouer*)malloc(sizeof(InterfaceJouer));
    builder = gtk_builder_new_from_file(VIEW_JOUER_PATH);

    ihmJouer->window = GTK_WIDGET(gtk_builder_get_object(builder, "windowJouer"));
    gtk_widget_set_name(ihmJouer->window, "windowJouer");

    ihmJouer->grille = GTK_WIDGET(gtk_builder_get_object(builder, "grille"));
    gtk_widget_set_name(ihmJouer->grille, "grille");

    ihmJouer->monPseudo = GTK_WIDGET(gtk_builder_get_object(builder, "monPseudo"));
    gtk_widget_set_name(ihmJouer->monPseudo, "monPseudo");

    ihmJouer->monScore = GTK_WIDGET(gtk_builder_get_object(builder, "monScore"));
    gtk_widget_set_name(ihmJouer->monScore, "monScore");

    ihmJouer->tempsValeur = GTK_WIDGET(gtk_builder_get_object(builder, "tempsValeur"));
    gtk_widget_set_name(ihmJouer->tempsValeur, "tempsValeur");

    ihmJouer->replayButton = GTK_WIDGET(gtk_builder_get_object(builder, "replayButton"));
    gtk_widget_set_name(ihmJouer->replayButton, "replayButton");


    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    return ihmJouer;
}
