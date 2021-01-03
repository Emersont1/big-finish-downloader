#pragma once
#include <libbf/login_cookie.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class preferences_window {
  GtkWidget * m4b_slider;
  GtkWidget * fallback_slider;
  GtkWidget * bonus_slider;
  GtkWidget * browse_button;
  GtkWidget * logout_button;
  GtkWidget * save_button;
  GtkWidget * cancel_button;
  GtkWidget * pathlabel;
  GtkWidget * window;

  GSettings * settings;

  static void ok_button_activate_cb(GtkWidget *, void *);
  static void cancel_button_cb(GtkWidget *, void *);

public:
  preferences_window();
};
} // namespace libbf::gui