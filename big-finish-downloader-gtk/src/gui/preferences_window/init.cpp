#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/modules/preferences_window.hpp>
#include <libbf/os/secret_storage.hpp>
#include <libbf/os/settings.hpp>
#include <libbf/os/dirs.hpp>

#include <glade_prefs.hpp>

libbf::gui::preferences_window::preferences_window(libbf::gui::main_window* parent)
        : parent(parent), changed_dir(false) {
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_string(builder, (const gchar*) GLADE_PREFS_STR.data(),
                                GLADE_PREFS_STR.size(), nullptr);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "pref_window"));
    gtk_builder_connect_signals(builder, NULL);

    m4b_slider = GTK_WIDGET(gtk_builder_get_object(builder, "m4b_slider"));
    fallback_slider = GTK_WIDGET(gtk_builder_get_object(builder, "fallback_slider"));
    bonus_slider = GTK_WIDGET(gtk_builder_get_object(builder, "bonus_slider"));
    browse_button = GTK_WIDGET(gtk_builder_get_object(builder, "browse_button"));
    logout_button = GTK_WIDGET(gtk_builder_get_object(builder, "logout_button"));
    save_button = GTK_WIDGET(gtk_builder_get_object(builder, "save_button"));
    cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    pathlabel = GTK_WIDGET(gtk_builder_get_object(builder, "pathlabel"));

    // set items to default settings values
    gtk_switch_set_active((GtkSwitch*) m4b_slider, parent->settings.get_prefer_m4b());
    gtk_switch_set_active((GtkSwitch*) fallback_slider, parent->settings.get_fallback_mp3());
    gtk_switch_set_active((GtkSwitch*) bonus_slider, parent->settings.get_download_extras());

    gtk_link_button_set_uri((GtkLinkButton*) pathlabel, (libbf::os::file_prefix() + parent->settings.get_path().string()).c_str());
    gtk_button_set_label(
            (GtkButton*) pathlabel,
            (std::string("Currently: ") + parent->settings.get_path().string())
                    .c_str());

    g_signal_connect(browse_button, "clicked", G_CALLBACK(&change_dir_cb), this);
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(&cancel_button_cb), this);
    g_signal_connect(logout_button, "clicked", G_CALLBACK(&logout_cb), this);
    g_signal_connect(save_button, "clicked", G_CALLBACK(&save_button_cb), this);
    g_signal_connect(window, "destroy", G_CALLBACK(&cancel_button_cb), this);

    g_object_unref(builder);

    gtk_widget_show(window);
}