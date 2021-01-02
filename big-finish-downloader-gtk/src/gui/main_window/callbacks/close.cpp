#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::close_cb(GtkWidget *wid, void *d){
    gtk_main_quit();
}