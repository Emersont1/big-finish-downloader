#include <iostream>

#include <libbf/gui/modules/login.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_login.hpp>

libbf::gui::login::login() {
  GtkBuilder * builder = gtk_builder_new();

  gtk_builder_add_from_string(builder, (const gchar *) GLADE_LOGIN_STR.data(),
                              GLADE_LOGIN_STR.size(), nullptr);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
  gtk_builder_connect_signals(builder, NULL);

  // get pointers to the two labels
  ok_button = GTK_WIDGET(gtk_builder_get_object(builder, "ok_button"));
  cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
  email_input = GTK_WIDGET(gtk_builder_get_object(builder, "email_entry"));
  password_input =
      GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));

  g_signal_connect(ok_button, "clicked", G_CALLBACK(&ok_button_activate_cb),
                   this);
  g_signal_connect(cancel_button, "clicked",
                   G_CALLBACK(&cancel_button_activate_cb), this);
  g_signal_connect(window, "destroy", G_CALLBACK(&cancel_button_activate_cb),
                   this);

  g_object_unref(builder);

  gtk_widget_show(window);
}

void libbf::gui::login::ok_button_activate_cb(GtkWidget * sender, void * d) {
  libbf::gui::login * l = (libbf::gui::login *) d;
  l->email = std::string(gtk_entry_get_text((GtkEntry *) l->email_input));
  l->password = std::string(gtk_entry_get_text((GtkEntry *) l->password_input));
  gtk_widget_destroy(l->window);
  gtk_main_quit();
}

void libbf::gui::login::cancel_button_activate_cb(GtkWidget * sender,
                                                  void *      d) {
  libbf::gui::login * l = (libbf::gui::login *) d;
  gtk_widget_destroy(l->window);
  gtk_main_quit();
}