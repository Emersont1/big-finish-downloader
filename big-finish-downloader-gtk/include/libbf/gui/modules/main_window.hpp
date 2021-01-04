#pragma once
#include <future>
#include <queue>
#include <thread>

#include <libbf/async_object.hpp>
#include <libbf/downloads.hpp>
#include <libbf/gui/modules/preferences_window.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
  std::string cache;

  std::thread                                         image_get_thread;
  std::promise<void>                                  image_get_close;
  std::queue<libbf::download>                         get_images;
  std::queue<std::pair<libbf::download, GdkPixbuf *>> got_images;

  libbf::async_getter<libbf::downloads_t> dl;

  std::unique_ptr<libbf::gui::preferences_window> p;

  GtkWidget * title_bar;
  GtkWidget * status_bar;
  GtkWidget * window;

  GtkListStore * list_downloading;
  GtkListStore * list_downloaded;
  GtkTreeView *  view_downloading;
  GtkWidget *    view_downloaded;

  GtkWidget * preferences_button;

  libbf::login_cookie cookie;

  static void close_cb(GtkWidget *, void *);
  static void prefs_cb(GtkWidget *, void *);
  static void toggle_cb(GtkCellRendererToggle *, char *, void *);

  static int update_func(void *);

  void do_get_images(std::future<void>);

public:
  main_window(libbf::login_cookie);
  ~main_window();
};
} // namespace libbf::gui