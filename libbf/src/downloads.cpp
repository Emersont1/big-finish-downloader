#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <vector>

#include <cpr/cpr.h>

#include <libbf/downloads.hpp>


std::filesystem::path libbf::download::download_mp3(
        libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
            std::filesystem::create_directories(std::filesystem::temp_directory_path() / "big-finish");
    cpr::Response pre_dl = cpr::Get(cpr::Url{"https://www.bigfinish.com/apiv3/downloadab/" +
                                             std::to_string(download_number) + ".json"}, cpr::Parameters{{"token", cookie.get_token()}});
    nlohmann::json pre_dl_js = nlohmann::json::parse(pre_dl.text);

    std::filesystem::path path = std::filesystem::temp_directory_path() / "big-finish" /
                                 pre_dl_js["download_info"]["filename"].get<std::string>();
    std::ofstream of(path, std::ios::binary);

    const cpr::WriteCallback cb([&](std::string data) -> bool {
        of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com" + pre_dl_js["download_info"]["download_url"].get<std::string>()},
                               cb, cpr::ProgressCallback{progress_callback}, cpr::Parameters{{"token", cookie.get_token()}});
    return path;
}

std::filesystem::path libbf::download::download_m4b(
        libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
            return download_mp3(cookie, progress_callback);
}

std::pair<std::filesystem::path, std::string> libbf::download::download_extra(
        std::pair<std::string, int> extra, libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
  return std::make_pair("/tmp", "err");
}