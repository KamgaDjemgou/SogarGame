#include "GameManager.h"


void initGTK(){
 //Initialisation du GTK
 if(!gtk_init_check(NULL, NULL)){
  exit(EXIT_FAILURE);
 }
}

void initGameManager(){
 gameManager = (GameManager*)malloc(sizeof(GameManager));
 gameManager->pageAccueil = initializeAccueil();
 gtk_widget_show_all(gameManager->pageAccueil->window);
}

void initStyle(){
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  const gchar *myCssFile = "style.css";
  GError *error = 0;

  gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);

  g_object_unref (provider);
}

void on_playButton_clicked(){
 const gchar* pseudoSaisi;
 pseudoSaisi = gtk_entry_get_text (GTK_ENTRY (gameManager->pageAccueil->pseudoEditor));

 //Cas de pseudo non saisi
 if(g_strcmp0(pseudoSaisi, "") == 0){
    afficherErreur(gameManager->pageAccueil->window, "Pseudo invalide !");
    return;
 }
 //Connexion au serveur
 if(connexionServeur(&(gameManager->socket)) < 0){
    afficherErreur(gameManager->pageAccueil->window, "Impossible de se connecter au serveur !");
    return;
 }

 gameManager->pageJouer = initializeJouer();
 bzero(gameManager->pseudo, TAILLE);
 strcpy(gameManager->pseudo, pseudoSaisi);
 gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->monPseudo), pseudoSaisi);
 insertImages();

 gtk_widget_hide(gameManager->pageAccueil->window);
 gtk_widget_show_all(gameManager->pageJouer->window);

 //Communication avec le serveur
 pthread_t thread;
 pthread_create(&thread, NULL,communicateWithServer,NULL);
}

void* communicateWithServer(void* arg){
     char buffer[TAILLE];
     bzero(buffer, TAILLE);

     if(recv(gameManager->socket, buffer, TAILLE, 0) > 0){
        gchar** split;
        split = g_strsplit(buffer, ":", -1);

        gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->tempsValeur), split[0]);
        gameManager->timing = atoi(split[0]);

        saveGrille(split[1]);

        gtk_widget_set_sensitive(gameManager->pageJouer->replayButton, FALSE);
        
        
        gameManager->tour = 0;
        gameManager->score = 0;
        g_timeout_add_seconds(30, (GSourceFunc)gererTemps, NULL);
        gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->monScore), "0");
     }
}

//Fonction pour la gestion du timing: A la fin de chaque 1/2 minute
void gererTemps(){
    if(gameManager->timing > 0){
      gameManager->timing--;
      char time[10];
      bzero(time, 10);
      char scoreActu[10];
      bzero(scoreActu, 10);

      sprintf(time, "%d", gameManager->timing);
      gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->tempsValeur), time);

      if(gameManager->timing == 0){

          for (int i = 0; i < TAILLE_GRILLE; ++i)
          {
            for (int j = 0; j < TAILLE_GRILLE; ++j)
            {
              gtk_widget_set_sensitive(gameManager->pageJouer->imagesBoutons[i][j], FALSE);
            }
          }

          afficherErreur(gameManager->pageJouer->window, "Fin de la partie");
          gtk_widget_set_sensitive(gameManager->pageJouer->replayButton, TRUE);
      }

    }
}

//Enregistrer la grille
void saveGrille(gchar* grilleMessage){
  gchar** split;
  split = g_strsplit(grilleMessage, " ",-1);
  int x, y;
  for (int i = 0; i < TAILLE_GRILLE*TAILLE_GRILLE; ++i)
  {
    x = i/TAILLE_GRILLE;
    y = i%TAILLE_GRILLE;

    gchar path[30];
    bzero(path, 30);
    sprintf(path, "resources/%s.png",split[i]);

    gameManager->pageJouer->imagesPaths[x][y] = (char*)malloc(30*sizeof(char));
    strcpy(gameManager->pageJouer->imagesPaths[x][y], path);
  }
}
void afficherErreur(GtkWidget* parent, const char* message){
    GtkWidget* dialog;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT|GTK_WIN_POS_CENTER_ALWAYS;
    dialog = gtk_message_dialog_new (GTK_WINDOW(parent),
    flags,
    GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,message, NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);
    g_signal_connect_swapped (dialog, "response",G_CALLBACK (gtk_widget_destroy),dialog);
}

void on_quit(){
  gtk_main_quit();
  send(gameManager->socket,QUIT, TAILLE, 0);
}

void startGame(){
 initGTK();
 initStyle();
 initGameManager();
 gtk_main();
}

//Recupérer la position du bouton dans la grille
void getPosButton(GtkWidget* button, int* x, int* y){
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if(gameManager->pageJouer->imagesBoutons[i][j] == button){
                *x = i;
                *y = j;
                return;
            }
        }
    }

}

//Insérer les images par défaut
void insertImages(){
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
            gtk_grid_attach(GTK_GRID(gameManager->pageJouer->grille), button, i, j, 1, 1);
            g_signal_connect(button, "clicked",G_CALLBACK (changeImage),button);
            gameManager->pageJouer->imagesBoutons[i][j] = button;
        }
    }
}

void resetImages(){
  GtkWidget*image;
  GtkWidget* button;
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            button = gameManager->pageJouer->imagesBoutons[i][j];
            image = gtk_image_new_from_file("resources/inconnu.png");

            gtk_button_set_image(GTK_BUTTON(button), image);
            gtk_widget_set_sensitive(button, TRUE);
        }
    }

}

//Changer une image
void changeImage(GtkWidget* button){
    int i, j;
    GtkWidget*image;

    getPosButton(button, &i, &j);
    image = gtk_image_new_from_file(gameManager->pageJouer->imagesPaths[i][j]);
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_sensitive(button, FALSE);

    if(gameManager->tour == 0){
        gameManager->firstButton = button;
    }
    gameManager->tour++;

    if(gameManager->tour == 2){
        int i1, j1;
        getPosButton(gameManager->firstButton, &i1, &j1);

        if(strcmp(gameManager->pageJouer->imagesPaths[i][j], gameManager->pageJouer->imagesPaths[i1][j1]) == 0){
            image = gtk_image_new_from_file("resources/correct.png");
            gtk_button_set_image(GTK_BUTTON(button), image);

            image = gtk_image_new_from_file("resources/correct.png");
            gtk_button_set_image(GTK_BUTTON(gameManager->firstButton), image);

            char score[10];
            gameManager->score += 2;
            sprintf(score, "%d", gameManager->score);
            gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->monScore), score);
            if(gameManager->score == 32){
                gtk_widget_set_sensitive(gameManager->pageJouer->replayButton, TRUE);
            }

        }else{
            image = gtk_image_new_from_file("resources/inconnu.png");
            gtk_button_set_image(GTK_BUTTON(button), image);

            image = gtk_image_new_from_file("resources/inconnu.png");
            gtk_button_set_image(GTK_BUTTON(gameManager->firstButton), image);
            gtk_widget_set_sensitive(button, TRUE);
            gtk_widget_set_sensitive(gameManager->firstButton, TRUE);
        }
        gameManager->tour = 0;

    }
}

//Lorsque le joueur veut rejouer
void onReplay(){
  resetImages();
  envoyerMessage(gameManager->socket, REPLAY);
  communicateWithServer(NULL);
}
