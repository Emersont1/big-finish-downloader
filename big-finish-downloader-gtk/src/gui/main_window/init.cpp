#include <iostream>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_main.hpp>

libbf::gui::main_window::main_window() {
  GtkBuilder * builder = gtk_builder_new();

  gtk_builder_add_from_string(builder, (const gchar *) GLADE_MAIN_STR.data(),
                              GLADE_MAIN_STR.size(), nullptr);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "downloader"));
  gtk_builder_connect_signals(builder, NULL);

  g_signal_connect(window, "destroy", G_CALLBACK(&close_cb), this);

  g_object_unref(builder);

  gtk_widget_show(window);
}