#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <config.hpp>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_main.hpp>

libbf::gui::main_window::main_window(libbf::login_cookie c) : cookie(c) {
  cache = std::string(std::getenv("HOME")) + "/.cache/big-finish/";
  if (!std::filesystem::exists(cache))
    std::filesystem::create_directory(cache);
  if (!std::filesystem::exists(cache + "img/"))
    std::filesystem::create_directory(cache + "img/");
  if (!std::filesystem::exists(cache + "locks/"))
    std::filesystem::create_directory(cache + "locks/");
  GtkBuilder * builder = gtk_builder_new();

  gtk_builder_add_from_string(builder, (const gchar *) GLADE_MAIN_STR.data(),
                              GLADE_MAIN_STR.size(), nullptr);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "downloader"));
  gtk_window_set_decorated((GtkWindow *) window, false);
  gtk_builder_connect_signals(builder, nullptr);

  g_signal_connect(window, "destroy", G_CALLBACK(&close_cb), this);

  status_bar = GTK_WIDGET(gtk_builder_get_object(builder, "status_bar"));
  gtk_label_set_text((GtkLabel *) status_bar,
                     ("You are logged in as: " + cookie.get_email()).c_str());

  title_bar = GTK_WIDGET(gtk_builder_get_object(builder, "title_bar"));
  gtk_header_bar_set_subtitle((GtkHeaderBar *) title_bar,
                              (std::string("Version: ") + PROJECT_VER).c_str());

  preferences_button =
      GTK_WIDGET(gtk_builder_get_object(builder, "pref_button"));
  g_signal_connect(preferences_button, "clicked", G_CALLBACK(&prefs_cb), this);

  list_downloading =
      (GtkListStore *) gtk_builder_get_object(builder, "downloading");
  list_downloaded =
      (GtkListStore *) gtk_builder_get_object(builder, "downloaded");
  view_downloading =
      GTK_TREE_VIEW(gtk_builder_get_object(builder, "view_downloading"));
  auto x = (GtkCellRendererToggle *) gtk_builder_get_object(
      builder, "col_download_toggle");

  g_signal_connect(x, "toggled", G_CALLBACK(&toggle_cb), this);
  g_object_unref(builder);

  gtk_widget_show(window);
  gdk_threads_add_timeout(100, &libbf::gui::main_window::update_func, this);

  image_get_thread =
      std::move(std::thread(&libbf::gui::main_window::do_get_images, this,
                            image_get_close.get_future()));
}

libbf::gui::main_window::~main_window() {
  image_get_close.set_value();
  image_get_thread.join();
}