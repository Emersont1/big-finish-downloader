#pragma once
#include <future>
#include <memory>
#include <thread>

#include <libbf/async_object.hpp>
#include <libbf/downloads.hpp>
#include <libbf/gui/modules/preferences_window.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
  libbf::async_getter<libbf::downloads_t> dl;

  std::unique_ptr<libbf::gui::preferences_window> p;

  GtkWidget * title_bar;
  GtkWidget * status_bar;
  GtkWidget * window;

  GtkWidget * preferences_button;

  libbf::login_cookie cookie;

  static void close_cb(GtkWidget *, void *);
  static void prefs_cb(GtkWidget *, void *);

  static int update_func(void *);

public:
  main_window(libbf::login_cookie);
};
} // namespace libbf::gui