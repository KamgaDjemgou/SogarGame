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

    ihmJouer->pseudoAdv = GTK_WIDGET(gtk_builder_get_object(builder, "pseudoAdv"));
    gtk_widget_set_name(ihmJouer->monPseudo, "pseudoAdv");

    ihmJouer->scoreAdv = GTK_WIDGET(gtk_builder_get_object(builder, "scoreAdv"));
    gtk_widget_set_name(ihmJouer->scoreAdv, "scoreAdv");

    ihmJouer->tempsValeur = GTK_WIDGET(gtk_builder_get_object(builder, "tempsValeur"));
    gtk_widget_set_name(ihmJouer->monPseudo, "tempsValeur");


    insertImages(ihmJouer);

    gtk_builder_connect_signals(builder, NULL);
    //gtk_signal_connect(G_OBJECT(ihmJouer->quitButton), "clicked", on_quitButton_clicked, NULL);

    g_object_unref(builder);

    return ihmJouer;
}

void insertImages(InterfaceJouer* ihmJouer){
    GtkWidget* button;
    GtkWidget*image;

    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            button = gtk_button_new();
            image = gtk_image_new_from_file("resources/inconnu.png");

            gtk_button_set_image(GTK_BUTTON(button), image);
            gtk_widget_set_name(button, "button");
            gtk_grid_attach(GTK_GRID(ihmJouer->grille), button, i, j, 1, 1);
            ihmJouer->imagesBoutons[i][j] = button;
        }
    }

}
