#include <iomanip>
#include <sstream>

#include <libbf/exceptions.hpp>
#include <libbf/gui/alert_box.hpp>
#include <libbf/gui/modules/login.hpp>
#include <libbf/gui/modules/main_window.hpp>
#include <libbf/os/dirs.hpp>
#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace alert = libbf::gui::alert;

int main(int argc, char** argv) {
    try {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream stream;
        stream << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");
        auto logger = spdlog::basic_logger_mt(
                "log", (libbf::os::get_cache() / "logs" / stream.str()).string());
        spdlog::set_default_logger(logger);
        spdlog::flush_every(std::chrono::seconds(3));
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }

    gtk_init(&argc, &argv);
    libbf::login_cookie c;
    try {
        // retrieve from libsecret
        c = libbf::os::retrieve();
        spdlog::info("retrieved info from secret store");
        if (!c.valid()) {
            spdlog::warn("Secret found but invalid");
            throw libbf::os::secret_not_found_exception();
        }
    } catch (libbf::os::secret_not_found_exception) {
        spdlog::warn("secret retrieved invalid or unable to retrieve info from secret store");
        // give loginform

        while (true) {
            libbf::gui::login l;
            gtk_main();

            try {
                c = libbf::login_cookie::login(l.email, l.password);
                spdlog::info("Successfully logged in");

                libbf::os::store(c);
                break;
            } catch (libbf::login_failed_exception) {
                spdlog::warn("login failed");
                if (alert::show("Username or password is incorrect, would you like to "
                                "try again?",
                                "Login Failed", alert::Style::Error,
                                alert::Buttons::YesNo) == alert::Selection::No)
                    return -1;
            } catch (libbf::os::secret_write_failed_exception) {
                spdlog::warn("Unable to Save Credentials");
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