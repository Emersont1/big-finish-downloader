#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <libbf/os/dirs.hpp>
#include <nlohmann/json.hpp>

#include <libbf/gui/modules/main_window.hpp>
#include <libbf/os/secret_storage.hpp>

libbf::gui::main_window::main_window(libbf::login_cookie c) : cookie(c) {
    quitter = std::shared_future<void>(quit.get_future());

    cache = libbf::os::get_cache();
    if (!std::filesystem::exists(cache))
        std::filesystem::create_directory(cache);
    if (!std::filesystem::exists(cache / "img"))
        std::filesystem::create_directory(cache / "img");
    if (!std::filesystem::exists(cache / "locks"))
        std::filesystem::create_directory(cache / "locks");

    download_progress = 0.0;

    widgets();
    load_downloaded();
}

libbf::gui::main_window::~main_window() {}