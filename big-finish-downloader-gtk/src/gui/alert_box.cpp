#include <gtk/gtk.h>
#include <libbf/gui/alert_box.hpp>

namespace alert = libbf::gui::alert;

alert::Selection alert::show(std::string message, std::string title, alert::Style style,
                             alert::Buttons buttons) {
    // Create a parent window to stop gtk_dialog_run from complaining
    GtkWidget* parent = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget* dialog =
            gtk_message_dialog_new(GTK_WINDOW(nullptr), GTK_DIALOG_MODAL, (GtkMessageType) style,
                                   (GtkButtonsType) buttons, "%s", message.c_str());
    gtk_window_set_title(GTK_WINDOW(dialog), title.c_str());
    auto selection = (alert::Selection) gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(GTK_WIDGET(dialog));
    gtk_widget_destroy(GTK_WIDGET(parent));
    /*while (g_main_context_iteration(nullptr, false))
      ;*/

    return selection;
}