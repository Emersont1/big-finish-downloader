#include <libbf/server/server.hpp>

#include <fstream>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <utils.hpp>
#include <zip_helper.hpp>

libbf::server::server::server()
        : close(false), download_thread(&libbf::server::server::download_loop, this) {
    if (!std::filesystem::exists(dest_path))
        std::filesystem::create_directories(dest_path);

    std::ifstream in(dest_path / "data.json", std::ios::in);
    if (in.is_open()) {
        nlohmann::json j;
        in >> j;
        processed_ids = j["ids"].get<std::set<int>>();
        downloaded_ids = j["ids"].get<std::set<int>>();
        auto _logins = j["logins"].get<std::vector<libbf::login_cookie>>();

        for (auto& x : _logins) {
            logins.push_back(std::make_shared<libbf::login_cookie>(x));
        }
        refresh_downloads();
    }
}