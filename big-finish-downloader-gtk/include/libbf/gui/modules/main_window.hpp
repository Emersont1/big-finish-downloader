#pragma once
#include <future>
#include <map>
#include <queue>
#include <thread>

#include <libbf/downloads.hpp>
#include <libbf/gui/modules/preferences_window.hpp>

#include <gtk/gtk.h>

namespace libbf::gui {
class main_window {
    std::string cache;

    std::promise<void> quit;
    std::future<int> downloader;
    double download_progress;
    std::string status_ii;

    std::future<std::vector<std::pair<libbf::download, GdkPixbuf*>>> items_fut;
    std::vector<std::pair<libbf::download, GdkPixbuf*>> items;
    std::vector<int> downloaded_ids;
    std::map<std::string, bool> shoud_download;

    GSettings* settings;
    std::string dest_dir;

    std::unique_ptr<libbf::gui::preferences_window> p;

    GtkWidget* title_bar;
    GtkWidget* status_bar;
    GtkWidget* downloading_label;
    GtkWidget* downloading_status_ii;
    GtkWidget* dest_dir_button;
    GtkWidget* window;

    GtkListStore* list_downloading;
    GtkListStore* list_downloaded;
    GtkTreeView* view_downloading;
    GtkWidget* view_downloaded;
    GtkWidget* thumbnail;
    GtkWidget* progress_bar;

    GtkWidget* preferences_button;

    libbf::login_cookie cookie;

    static void close_cb(GtkWidget*, void*);
    static void prefs_cb(GtkWidget*, void*);
    static void toggle_cb(GtkCellRendererToggle*, char*, void*);

    static int update_func(void*);

    std::vector<std::pair<libbf::download, GdkPixbuf*>> get_items(libbf::login_cookie c);

    void widgets();
    void load_downloaded();
    int download(libbf::download, std::future<void>);

    void add_to_view(std::pair<libbf::download, GdkPixbuf*>&);

  public:
    main_window(libbf::login_cookie);
    ~main_window();
    void changed_dir();
};
} // namespace libbf::gui