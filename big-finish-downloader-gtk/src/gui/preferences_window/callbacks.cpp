#include <iostream>

#include <libbf/gui/alert_box.hpp>
#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/modules/preferences_window.hpp>
#include <libbf/os/secret_storage.hpp>
#include <libbf/os/dirs.hpp>

#include <glade_prefs.hpp>

void libbf::gui::preferences_window::cancel_button_cb(GtkWidget* sender, void* d) {
    auto l = (libbf::gui::preferences_window*) d;
    gtk_widget_destroy(l->window);
}

void libbf::gui::preferences_window::save_button_cb(GtkWidget* sender, void* d) {
    auto l = (libbf::gui::preferences_window*) d;

    l->parent->settings.set_prefer_m4b(
                           gtk_switch_get_active((GtkSwitch*) l->m4b_slider));
    l->parent->settings.set_fallback_mp3(
                           gtk_switch_get_active((GtkSwitch*) l->fallback_slider));
    l->parent->settings.set_download_extras(
                           gtk_switch_get_active((GtkSwitch*) l->bonus_slider));

    // now flatten the path
    std::string path(gtk_link_button_get_uri((GtkLinkButton*) l->pathlabel));
    std::string p = libbf::os::file_prefix();
    if(!p.empty()){
    if (path.rfind(p, 0) == 0) {
        path = path.substr(p.size());
    }}

    l->parent->settings.set_path(path);

    gtk_widget_destroy(l->window);

    if (l->changed_dir) {
        std::cout << std::endl;
        l->parent->changed_dir();
    }
}

void libbf::gui::preferences_window::change_dir_cb(GtkWidget* sender, void* d) {
    auto l = (libbf::gui::preferences_window*) d;

    GtkWidget* dialog =
            gtk_file_chooser_dialog_new("Select Destination Directory", (GtkWindow*) l->window,
                                        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "_Cancel",
                                        GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, nullptr);
    GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    int res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        auto filename = gtk_file_chooser_get_filename(chooser);
        std::string path(filename);
        auto p = libbf::os::get_home();
        std::string p2 = path;
        gtk_link_button_set_uri((GtkLinkButton*) l->pathlabel, (libbf::os::file_prefix() + path).c_str());
        gtk_button_set_label((GtkButton*) l->pathlabel, ("Currently: " + p2).c_str());
        g_free(filename);
        l->changed_dir = true;
    }

    gtk_widget_destroy(dialog);
}

void libbf::gui::preferences_window::logout_cb(GtkWidget* sender, void* d) {
    auto l = (libbf::gui::preferences_window*) d;
    auto x = alert::show("Would you like to log out?\nIf so the problem will close",
                         "Confirm Logout", alert::Style::Question, alert::Buttons::YesNo);

    if (x == alert::Selection::Yes) {
        libbf::os::revoke();
        gtk_widget_destroy(l->window);
        gtk_main_quit();
    }
    gtk_main_quit();
}