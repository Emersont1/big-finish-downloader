#include <iostream>

#include <config.hpp>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_main.hpp>

libbf::gui::main_window::main_window(libbf::login_cookie c) : cookie(c) {

  GtkBuilder * builder = gtk_builder_new();

  gtk_builder_add_from_string(builder, (const gchar *) GLADE_MAIN_STR.data(),
                              GLADE_MAIN_STR.size(), nullptr);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "downloader"));
  gtk_builder_connect_signals(builder, NULL);

  g_signal_connect(window, "destroy", G_CALLBACK(&close_cb), this);

  status_bar = GTK_WIDGET(gtk_builder_get_object(builder, "status_bar"));
  gtk_label_set_text((GtkLabel *) status_bar,
                     ("You are logged in as: " + cookie.get_email()).c_str());

  title_bar = status_bar =
      GTK_WIDGET(gtk_builder_get_object(builder, "title_bar"));
  gtk_header_bar_set_subtitle((GtkHeaderBar *) status_bar,
                              (std::string("Version: ") + PROJECT_VER).c_str());

  g_object_unref(builder);

  gtk_widget_show(window);
  gdk_threads_add_idle(&libbf::gui::main_window::update_func, this);
}