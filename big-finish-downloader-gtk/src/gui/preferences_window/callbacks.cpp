#include <iostream>

#include <libbf/gui/modules/preferences_window.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_prefs.hpp>

void libbf::gui::preferences_window::cancel_button_cb(GtkWidget * sender,
                                                      void *      d) {
  auto l = (libbf::gui::preferences_window *) d;
  gtk_widget_destroy(l->window);
}