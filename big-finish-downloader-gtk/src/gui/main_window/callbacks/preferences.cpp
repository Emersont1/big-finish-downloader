#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::prefs_cb(GtkWidget * wid, void * d) {
  auto m = (libbf::gui::main_window *) d;
  m->p = std::make_unique<libbf::gui::preferences_window>();
}