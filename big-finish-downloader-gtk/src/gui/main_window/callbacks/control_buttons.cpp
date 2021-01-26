#include <fstream>
#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::refresh_button_cb(GtkWidget* wid, void* d) {
    auto m = (libbf::gui::main_window*) d;
    m->items_fut =
            std::async(std::launch::async, &libbf::gui::main_window::get_items, m, m->cookie);
}
void libbf::gui::main_window::start_download_cb(GtkWidget* wid, void* d) {
    auto m = (libbf::gui::main_window*) d;
    m->settings.set_download_automatically(true);
}

void libbf::gui::main_window::stop_after_cb(GtkWidget* wid, void* d) {
    auto m = (libbf::gui::main_window*) d;
    m->settings.set_download_automatically(false);
}
void libbf::gui::main_window::stop_now_cb(GtkWidget* wid, void* d) {
    auto m = (libbf::gui::main_window*) d;
    m->settings.set_download_automatically(false);

    // Stop the Download!
    m->quit.set_value();
    if (m->downloader.valid()) {
        m->downloader.get();

        auto item = std::find_if(m->items.begin(), m->items.end(),
                                 [&](std::pair<libbf::download, GdkPixbuf*> i) {
                                     return i.first.image_number == m->currently_downloading;
                                 });
        if (item != m->items.end())
            m->add_to_view(*item);
        m->download_progress = 0.0;
    }
    // reset promise
    m->quit = std::promise<void>();
    m->quitter = std::shared_future<void>(m->quit.get_future());
}
