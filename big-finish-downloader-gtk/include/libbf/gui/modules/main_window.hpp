#pragma once
#include <future>
#include <map>
#include <queue>
#include <thread>

#include <libbf/async_object.hpp>
#include <libbf/downloads.hpp>
#include <libbf/gui/modules/preferences_window.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
  std::string cache;

  libbf::async_getter<int> downloader;
  double                   download_progress;
  std::uint64_t            download_size; // maybe use this

  std::thread                                         image_get_thread;
  std::promise<void>                                  image_get_close;
  std::queue<libbf::download>                         get_images;
  std::queue<std::pair<libbf::download, GdkPixbuf *>> got_images;

  std::map<int, std::pair<libbf::download, GdkPixbuf *>> items;
  std::vector<int>                                       downloaded_ids;
  std::map<std::string, bool>                            shoud_download;

  GSettings * settings;
  std::string dest_dir;

  libbf::async_getter<libbf::downloads_t> items_scrape;

  std::unique_ptr<libbf::gui::preferences_window> p;

  GtkWidget * title_bar;
  GtkWidget * status_bar;
  GtkWidget * dest_dir_button;
  GtkWidget * window;

  GtkListStore * list_downloading;
  GtkListStore * list_downloaded;
  GtkTreeView *  view_downloading;
  GtkWidget *    view_downloaded;
  GtkWidget *    thumbnail;
  GtkWidget *    progress_bar;

  GtkWidget * preferences_button;

  libbf::login_cookie cookie;

  static void close_cb(GtkWidget *, void *);
  static void prefs_cb(GtkWidget *, void *);
  static void toggle_cb(GtkCellRendererToggle *, char *, void *);

  static int update_func(void *);

  void do_get_images(std::future<void>);

  void widgets();
  void load_downloaded();
  int  download(int);

  void add_to_view(std::pair<libbf::download, GdkPixbuf *> &);

public:
  main_window(libbf::login_cookie);
  ~main_window();
  void changed_dir();
};
} // namespace libbf::gui