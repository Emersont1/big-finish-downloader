#include <iostream>

#include <libbf/gui/alert_box.hpp>
#include <libbf/gui/modules/preferences_window.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <glade_prefs.hpp>

void libbf::gui::preferences_window::cancel_button_cb(GtkWidget * sender,
                                                      void *      d) {
  auto l = (libbf::gui::preferences_window *) d;
  gtk_widget_destroy(l->window);
}

void libbf::gui::preferences_window::save_button_cb(GtkWidget * sender,
                                                    void *      d) {
  auto l = (libbf::gui::preferences_window *) d;

  g_settings_set_boolean(l->settings, "prefer-m4b",
                         gtk_switch_get_active((GtkSwitch *) l->m4b_slider));
  g_settings_set_boolean(
      l->settings, "fallback-mp3",
      gtk_switch_get_active((GtkSwitch *) l->fallback_slider));
  g_settings_set_boolean(l->settings, "download-extras",
                         gtk_switch_get_active((GtkSwitch *) l->bonus_slider));

  // now flatten the path
  std::string path(gtk_link_button_get_uri((GtkLinkButton *) l->pathlabel));
  auto        p = "file://" + std::string(std::getenv("HOME"));

  if (path.rfind(p, 0) == 0) {
    path = "~" + path.substr(p.size());
  }

  g_settings_set_string(l->settings, "download-directory", path.c_str());
  gtk_widget_destroy(l->window);
}

void libbf::gui::preferences_window::change_dir_cb(GtkWidget * sender,
                                                   void *      d) {
  auto l = (libbf::gui::preferences_window *) d;

  GtkWidget * dialog = gtk_file_chooser_dialog_new(
      "Select Destination Directory", (GtkWindow *) l->window,
      GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "_Cancel", GTK_RESPONSE_CANCEL,
      "_Save", GTK_RESPONSE_ACCEPT, nullptr);
  GtkFileChooser * chooser = GTK_FILE_CHOOSER(dialog);

  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

  int res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {

    auto        filename = gtk_file_chooser_get_filename(chooser);
    std::string path(filename);
    auto        p = std::string(std::getenv("HOME"));
    std::string p2 = path;
    if (path.rfind(p, 0) == 0) {
      p2 = "~" + path.substr(p.size());
    }
    gtk_link_button_set_uri((GtkLinkButton *) l->pathlabel,
                            ("file://" + path).c_str());
    gtk_button_set_label((GtkButton *) l->pathlabel,
                         ("Currently: " + p2).c_str());
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

void libbf::gui::preferences_window::logout_cb(GtkWidget * sender, void * d) {
  auto l = (libbf::gui::preferences_window *) d;
  auto x = alert::show(
      "Would you like to log out?\nIf so the problem will close",
      "Confirm Logout", alert::Style::Question, alert::Buttons::YesNo);

  if (x == alert::Selection::Yes) {
    libbf::gui::revoke();
    gtk_widget_destroy(l->window);
    gtk_main_quit();
  }
  gtk_main_quit();
}