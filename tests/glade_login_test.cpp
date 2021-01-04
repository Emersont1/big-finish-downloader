#include <glade_login.hpp>
#include <gtk/gtk.h>
#include <iostream>

GtkWidget* ok_button;
GtkWidget* cancel_button;
GtkWidget* email_input;
GtkWidget* password_input;

void ok_button_activate_cb();
void cancel_button_activate_cb();

int main(int argc, char** argv) {
    GtkBuilder* builder;
    GtkWidget* window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_string(builder, (const gchar*) GLADE_LOGIN_STR.data(),
                                GLADE_LOGIN_STR.size(), nullptr);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_builder_connect_signals(builder, NULL);

    // get pointers to the two labels
    ok_button = GTK_WIDGET(gtk_builder_get_object(builder, "ok_button"));
    cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    email_input = GTK_WIDGET(gtk_builder_get_object(builder, "email_entry"));
    password_input = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));

    g_signal_connect(ok_button, "clicked", G_CALLBACK(ok_button_activate_cb), NULL);
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(cancel_button_activate_cb), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(cancel_button_activate_cb), NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

// called when button is clicked
void ok_button_activate_cb() {
    std::cout << "click" << std::endl
              << gtk_entry_get_text((GtkEntry*) email_input) << std::endl
              << gtk_entry_get_text((GtkEntry*) password_input) << std::endl;
}

// called when window is closed
void cancel_button_activate_cb() {
    gtk_main_quit();
}