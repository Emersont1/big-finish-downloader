#pragma once
#include <libbf/login_cookie.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class login {
    GtkWidget* ok_button;
    GtkWidget* cancel_button;
    GtkWidget* email_input;
    GtkWidget* password_input;
    GtkWidget* window;

    static void ok_button_activate_cb(GtkWidget*, void*);
    static void cancel_button_activate_cb(GtkWidget*, void*);

  public:
    login();
    std::string email, password;
};
} // namespace libbf::gui