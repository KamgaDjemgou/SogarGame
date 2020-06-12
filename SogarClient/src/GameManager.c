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

void startGame(){
 initGTK();
 initStyle();
 initGameManager();
 gtk_main();
}
