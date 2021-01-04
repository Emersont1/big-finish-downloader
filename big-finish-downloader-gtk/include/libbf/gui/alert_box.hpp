#pragma once
#include <string>

#include <gtk/gtk.h>

//~~shamelessly stolen~~ adapted from aaronmjacobs/Boxer

namespace libbf::gui::alert {

/*!
 * Options for styles to apply to a message box
 */
enum class Style {
    Info = GTK_MESSAGE_INFO,
    Warning = GTK_MESSAGE_WARNING,
    Error = GTK_MESSAGE_ERROR,
    Question = GTK_MESSAGE_QUESTION
};

/*!
 * Options for buttons to provide on a message box
 */
enum class Buttons {
    OK = GTK_BUTTONS_OK,
    OKCancel = GTK_BUTTONS_OK_CANCEL,
    YesNo = GTK_BUTTONS_YES_NO,
    Quit = GTK_BUTTONS_CLOSE
};

/*!
 * Possible responses from a message box. 'None' signifies that no option was
 * chosen, and 'Error' signifies that an error was encountered while creating
 * the message box.
 */
enum class Selection {
    OK = GTK_RESPONSE_OK,
    Cancel = GTK_RESPONSE_CANCEL,
    Yes = GTK_RESPONSE_YES,
    No = GTK_RESPONSE_NO,
    Quit = GTK_RESPONSE_CLOSE,
    None = -1,
    Error = -2
};

Selection show(std::string message, std::string title, Style style = Style::Info,
               Buttons buttons = Buttons::OK);

} // namespace libbf::gui::alert