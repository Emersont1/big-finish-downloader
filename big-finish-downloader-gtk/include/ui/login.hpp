#include <gtk/gtk.h>

#include <libbf/login_cookie.hpp>

namespace ui {
class login {
  GtkWidget * ok_button;
  GtkWidget * cancel_button;
  GtkWidget * email_input;
  GtkWidget * password_input;
  GtkWidget * window;

  libbf::login_cookie cookie;

  static void ok_button_activate_cb(GtkWidget *, void *);
  static void cancel_button_activate_cb(GtkWidget *, void *);

public:
  login();
  void show() { gtk_widget_show(window); }
};
} // namespace ui