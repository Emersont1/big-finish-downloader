#include <libbf/gui/modules/main_window.hpp>

#include <config.hpp>
#include <glade_main.hpp>

void libbf::gui::main_window::widgets() {
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

  dest_dir_button =
      GTK_WIDGET(gtk_builder_get_object(builder, "destination_dir"));
  progress_bar = GTK_WIDGET(gtk_builder_get_object(builder, "progress_bar"));
  thumbnail = GTK_WIDGET(gtk_builder_get_object(builder, "thumbnail"));
  gtk_image_set_from_icon_name((GtkImage *) thumbnail, "media-optical",
                               GTK_ICON_SIZE_DIALOG);

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
}