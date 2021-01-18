#include <iostream>
#include <gtk/gtk.h>

void link_cb(GtkWidget* w){
    auto p = gtk_link_button_get_uri((GtkLinkButton*)w);
    std::system(p);
}