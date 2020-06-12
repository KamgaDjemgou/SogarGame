#include "InterfaceAccueil.h"

InterfaceAccueil* initializeAccueil(){
    InterfaceAccueil *ihmAccueil;
	GtkBuilder *builder;


	ihmAccueil = (InterfaceAccueil*)malloc(sizeof(InterfaceAccueil));
    builder = gtk_builder_new_from_file(VIEW_ACCUEIL_PATH);

    ihmAccueil->window = GTK_WIDGET(gtk_builder_get_object(builder, "windowAccueil"));
    gtk_widget_set_name(ihmAccueil->window, "windowAccueil");

    ihmAccueil->titleGame = GTK_WIDGET(gtk_builder_get_object(builder, "titleGame"));
    gtk_widget_set_name(ihmAccueil->titleGame, "titleGame");

    ihmAccueil->pseudoEditor  = GTK_WIDGET(gtk_builder_get_object(builder, "pseudoEditor"));
    gtk_widget_set_name(ihmAccueil->pseudoEditor, "pseudoEditor");

    ihmAccueil->playButton = GTK_WIDGET(gtk_builder_get_object(builder, "playButton"));
    gtk_widget_set_name(ihmAccueil->playButton, "playButton");

    ihmAccueil->quitButton = GTK_WIDGET(gtk_builder_get_object(builder, "quitButton"));
    gtk_widget_set_name(ihmAccueil->quitButton, "quitButton");

    gtk_builder_connect_signals(builder, NULL);
    //gtk_signal_connect(G_OBJECT(ihmAccueil->quitButton), "clicked", on_quitButton_clicked, NULL);

    g_object_unref(builder);

    return ihmAccueil;
}
