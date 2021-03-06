#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <vector>

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <utils.hpp>

#include <libbf/downloads.hpp>

std::filesystem::path tempname() {
    size_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    std::filesystem::create_directories(std::filesystem::temp_directory_path() / "big-finish");
    return std::filesystem::temp_directory_path() / "big-finish" / std::to_string(ms);
}

std::filesystem::path libbf::download::download_mp3(
        libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
    std::filesystem::path path = tempname();

    spdlog::info("Downloading MP3 of \"{}\" to {}", name, path.generic_string());

    std::ofstream of(path, std::ios::binary);

    const cpr::WriteCallback cb([&](std::string data) -> bool {
        of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com/releases/download/" +
                                        std::to_string(download_number)},
                               cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                                            {"CAKEPHP", cookie.get_cakephp()}},
                               cb, cpr::ProgressCallback{progress_callback});
    spdlog::info("Download: Got Status Code: {}", r.status_code);
    if (r.status_code != 200) {
        spdlog::warn(r.error.message);
    }
    for (auto& x : r.header) {
        spdlog::info("Header[{}] = {}", x.first, x.second);
    }
    return path;
}

std::filesystem::path libbf::download::download_m4b(
        libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
    std::filesystem::path path = tempname();

    spdlog::info("Downloading M4B of \"{}\" to {}", name, path.generic_string());

    std::ofstream of(path, std::ios::binary);

    const cpr::WriteCallback cb([&](std::string data) -> bool {
        of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com/releases/download/" +
                                        std::to_string(download_number) + "/audiobook"},
                               cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                                            {"CAKEPHP", cookie.get_cakephp()}},
                               cb, cpr::ProgressCallback{progress_callback});
    spdlog::info("Download: Got Status Code: {}", r.status_code);
    if (r.status_code != 200) {
        spdlog::warn(r.error.message);
    }
    for (auto& x : r.header) {
        spdlog::info("Header[{}] = {}", x.first, x.second);
    }
    return path;
}

std::pair<std::filesystem::path, std::string> libbf::download::download_extra(
        std::pair<std::string, int> extra, libbf::login_cookie& cookie,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
    std::filesystem::path path = tempname();

    spdlog::info("Downloading Bonus Content \"{} - {}\" to {}", name, extra.second,
                 path.generic_string());

    std::ofstream of(path, std::ios::binary);

    const cpr::WriteCallback cb([&](std::string data) -> bool {
        of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Response r =
            cpr::Get(cpr::Url{"https://www.bigfinish.com/releases/downloadsupplementarymedia/" +
                              std::to_string(extra.second)},
                     cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                                  {"CAKEPHP", cookie.get_cakephp()}},
                     cb, cpr::ProgressCallback{progress_callback});

    spdlog::info("Download: Got Status Code: {}", r.status_code);
    if (r.status_code != 200) {
        spdlog::warn(r.error.message);
    }
    for (auto& x : r.header) {
        spdlog::info("Header[{}] = {}", x.first, x.second);
    }

    // parse "Content-Disposition"
    std::stringstream s;
    s << r.header["Content-Disposition"];
    std::string value, extension;
    while (std::getline(s, value, ';')) {
        trim(value);
        if (value.substr(0, 10) == "filename=\"") {
            value.pop_back();
            extension = value.substr(value.find_last_of(".") + 1);
        }
    }


    return std::make_pair(path, extension);
}