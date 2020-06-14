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

 gtk_widget_hide(gameManager->pageAccueil->window);
 gtk_widget_show_all(gameManager->pageJouer->window);

 GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT|GTK_DIALOG_MODAL;
 gameManager->dialog = gtk_message_dialog_new (GTK_WINDOW(gameManager->pageJouer->window),
 flags,
 GTK_MESSAGE_ERROR,GTK_BUTTONS_CANCEL,"En attente de votre adversaire ...", NULL);
 gtk_window_set_position(GTK_WINDOW(gameManager->dialog), GTK_WIN_POS_CENTER_ON_PARENT);
 g_signal_connect(gameManager->dialog, "response",G_CALLBACK (on_quit),NULL);

 gtk_widget_show_all(gameManager->dialog);

 //Communication avec le serveurs
 pthread_t thread;
 pthread_create(&thread, NULL,communicateWithServer,NULL);
}

void* communicateWithServer(void* arg){
     envoyerMessage(gameManager->socket, gameManager->pseudo);

     char buffer[TAILLE];
     bzero(buffer, TAILLE);
     if(recv(gameManager->socket, buffer, TAILLE, 0) > 0){
        gtk_widget_destroy(gameManager->dialog);

        gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->pseudoAdv), buffer);
        gtk_label_set_text(GTK_LABEL(gameManager->pageJouer->scoreAdv), "0");
     }
}

void afficherErreur(GtkWidget* parent, const char* message){
    GtkWidget* dialog;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_message_dialog_new (GTK_WINDOW(parent),
    flags,
    GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,message, NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);
    g_signal_connect_swapped (dialog, "response",G_CALLBACK (gtk_widget_destroy),dialog);
}

void on_quit(){
  gtk_main_quit();
  send(gameManager->socket,QUIT, strlen(TAILLE), 0);
}


void startGame(){
 initGTK();
 initStyle();
 initGameManager();
 gtk_main();
}
