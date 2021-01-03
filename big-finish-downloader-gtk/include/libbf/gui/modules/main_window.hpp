#include <libbf/login_cookie.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
  GtkWidget * title_bar;
  GtkWidget * status_bar;
  GtkWidget * window;

  libbf::login_cookie cookie;

  static void close_cb(GtkWidget *, void *);

public:
  main_window(libbf::login_cookie);
};
} // namespace libbf::gui