#include <libbf/login_cookie.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
  GtkWidget * ok_button;
  GtkWidget * cancel_button;
  GtkWidget * email_input;
  GtkWidget * password_input;
  GtkWidget * window;

  libbf::login_cookie cookie;

  static void close_cb(GtkWidget *, void *);

public:
  main_window();
};
} // namespace libbf::gui