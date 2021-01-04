#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::load_downloaded() {
  downloaded_ids.clear();
  std::ifstream i(std::filesystem::path(dest_dir) / ".downloaded.json");

  if (i.is_open()) {
    nlohmann::json j;
    i >> j;
    downloaded_ids = j["downloaded_ids"].get<std::vector<int>>();
    shoud_download = j["shoud_download"].get<std::map<std::string, bool>>();
  }

  gtk_link_button_set_uri((GtkLinkButton *) dest_dir_button,
                          ("file://" + dest_dir).c_str());
  gtk_button_set_label((GtkButton *) dest_dir_button,
                       ("Open Library folder (" + dest_dir + ")").c_str());
}

void libbf::gui::main_window::add_to_view(
    std::pair<libbf::download, GdkPixbuf *> & x) {
  if (std::find(downloaded_ids.begin(), downloaded_ids.end(),
                x.first.download_number) != downloaded_ids.end()) {
    gtk_list_store_insert_with_values(list_downloaded, nullptr, -1, 0,
                                      x.first.name.c_str(), 1, x.second, -1);
  } else {
    bool e = shoud_download.count(std::to_string(x.first.download_number))&&shoud_download[std::to_string(x.first.download_number)];
    gtk_list_store_insert_with_values(list_downloading, nullptr, -1, 0,
                                      x.first.name.c_str(), 1, !e, 2, x.second,
                                      3, x.first.download_number, -1);
  }
}