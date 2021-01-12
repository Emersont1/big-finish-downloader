#pragma once
#include <libbf/login_cookie.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window;
class preferences_window {
    GtkWidget* m4b_slider;
    GtkWidget* fallback_slider;
    GtkWidget* bonus_slider;
    GtkWidget* browse_button;
    GtkWidget* logout_button;
    GtkWidget* save_button;
    GtkWidget* cancel_button;
    GtkWidget* pathlabel;
    GtkWidget* window;

    libbf::gui::main_window* parent;
    bool changed_dir;

    static void change_dir_cb(GtkWidget*, void*);
    static void cancel_button_cb(GtkWidget*, void*);
    static void save_button_cb(GtkWidget*, void*);
    static void logout_cb(GtkWidget*, void*);

  public:
    preferences_window(libbf::gui::main_window*);
};
} // namespace libbf::gui