#include "GameManager.h"



int main(int argc, char *argv[])
{
 startGame();
 return 0;
}





/*#define ROWS 6
#define COLUMNS 6

GtkWidget *pseudoEntry;
GtkWidget *grille;

PangoAttrList *attrlist;
PangoAttribute *attr;
PangoFontDescription *df;

void on_playWindow_destroy();


void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);


    g_object_unref (provider);

}

void treat(){
    attrlist = pango_attr_list_new();

// First, let's set up the base attributes.
// This part is copied from your code (and slightly bugfixed and reformatted):
df = pango_font_description_new();
pango_font_description_set_family(df, "Arial Rounded MT");
//pango_font_description_set_size(df, 15);
pango_font_description_set_weight(df, PANGO_WEIGHT_BOLD);
// You can also use pango_font_description_new_from_string() and pass in a string like "Arial Rounded MT Bold (whatever fontsize is)".
// But here's where things change:
attr = pango_attr_font_desc_new(df);
// This is not documented, but pango_attr_font_desc_new() makes a copy of df, so let's release ours:
pango_font_description_free(df);
// Pango and GTK+ use UTF-8, so our string is indexed between 0 and 11.
// Note that the end_index is exclusive!
attr->start_index = 0;
attr->end_index = 11;
pango_attr_list_insert(attrlist, attr);
// And pango_attr_list_insert() takes ownership of attr, so we don't free it ourselves.
// As an alternative to all that, you can have each component of the PangoFontDescriptor be its own attribute; see the PangoAttribute documentation page.

// And now the attribute for the word "World".
attr = pango_attr_family_new("Arial");
// "World" starts at 6 and ends at 11.
attr->start_index = 6;
attr->end_index = 11;
pango_attr_list_insert(attrlist, attr);

}


// And finally, give the GtkLabel our attribute list.

int main(int argc, char *argv[])
{
    // GtkBuilder      *builder;
    // GtkWidget       *window;

    // gtk_init(&argc, &argv);

    // builder = gtk_builder_new_from_file("glade/main_window.glade");

    // window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // pseudoEntry  = GTK_WIDGET(gtk_builder_get_object(builder, "pseudoEntry"));
    // gtk_builder_connect_signals(builder, NULL);

    // g_object_unref(builder);

    // gtk_widget_show(window);
    // gtk_main();

    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *labelTemps;
    //GtkWidget       *valeurTemps


    gtk_init(&argc, &argv);
    myCSS();
    treat();
    builder = gtk_builder_new_from_file("glade/playWindow.glade");
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "playWindow"));
    grille = GTK_WIDGET(gtk_builder_get_object(builder, "grille"));
    gtk_widget_set_name(grille, "grille");
    labelTemps = GTK_WIDGET(gtk_builder_get_object(builder, "pseudo"));
    gtk_label_set_attributes(GTK_LABEL(labelTemps), attrlist);
    GtkWidget* button;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            button = gtk_button_new_with_label("button");
            gtk_widget_set_name(button, "bouton");
            gtk_grid_attach(GTK_GRID(grille), button, i, j, 1, 1);
        }
    }


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void on_playButton_clicked(){
    const gchar* text;
    text = gtk_entry_get_text (GTK_ENTRY (pseudoEntry));
    printf("Text entered: %s\n", text);
}

void on_playWindow_destroy(){
    gtk_main_quit();
}*/
