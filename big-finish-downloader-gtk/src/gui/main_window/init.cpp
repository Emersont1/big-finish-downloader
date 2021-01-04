#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/gui/secret_storage.hpp>

libbf::gui::main_window::main_window(libbf::login_cookie c) : cookie(c) {
  cache = std::string(std::getenv("HOME")) + "/.cache/big-finish/";
  if (!std::filesystem::exists(cache))
    std::filesystem::create_directory(cache);
  if (!std::filesystem::exists(cache + "img/"))
    std::filesystem::create_directory(cache + "img/");
  if (!std::filesystem::exists(cache + "locks/"))
    std::filesystem::create_directory(cache + "locks/");

  settings = g_settings_new("uk.et1.big-finish");
  dest_dir = std::string(g_settings_get_string(settings, "download-directory"));
  if (dest_dir[0] == '~') {
    dest_dir = std::getenv("HOME") + dest_dir.substr(1);
  }

  widgets();
  load_downloaded();
}

libbf::gui::main_window::~main_window() {
  quit.set_value();
  std::ofstream  o(std::filesystem::path(dest_dir) / ".downloaded.json");
  nlohmann::json j;
  j["downloaded_ids"] = downloaded_ids;
  j["shoud_download"] = shoud_download;
  o << j;
}