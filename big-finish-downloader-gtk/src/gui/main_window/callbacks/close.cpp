#include <fstream>
#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::close_cb(GtkWidget* wid, void* d) {
    auto m = (libbf::gui::main_window*) d;
    m->quit.set_value();
    std::ofstream o(m->settings.get_path() / ".downloaded.json");
    nlohmann::json j;
    j["downloaded_ids"] = m->downloaded_ids;
    j["shoud_download"] = m->shoud_download;
    o << j;
    gtk_main_quit();
}