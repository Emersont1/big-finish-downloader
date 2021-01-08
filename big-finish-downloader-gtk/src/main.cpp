#include <libbf/exceptions.hpp>
#include <libbf/gui/alert_box.hpp>
#include <libbf/gui/modules/login.hpp>
#include <libbf/gui/modules/main_window.hpp>
#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>

namespace alert = libbf::gui::alert;

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
    libbf::login_cookie c;
    try {
        // retrieve from libsecret
        c = libbf::os::retrieve();
        if (!c.valid()) {
            throw libbf::os::secret_not_found_exception();
        }
    } catch (libbf::os::secret_not_found_exception) {
        // give loginform

        while (true) {
            libbf::gui::login l;
            gtk_main();

            try {
                c = libbf::login_cookie::login(l.email, l.password);
                libbf::os::store(c);
                break;
            } catch (libbf::login_failed_exception) {
                std::cerr << "login failed" << std::endl;
                if (alert::show("Username or password is incorrect, would you like to "
                                "try again?",
                                "Login Failed", alert::Style::Error,
                                alert::Buttons::YesNo) == alert::Selection::No)
                    return -1;
            } catch (libbf::os::secret_write_failed_exception) {
                alert::show(
                        "Unable to save credentials to store. The program will continue as "
                        "normal, but you will have to re-enter your details when you next "
                        "open this program",
                        "Saving credentials failed!", alert::Style::Warning, alert::Buttons::OK);
                break;
            }
        }
    }

    libbf::gui::main_window x(c);
    gtk_main();
}