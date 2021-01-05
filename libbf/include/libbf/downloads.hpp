#pragma once

#include <filesystem>
#include <future>
#include <string>
#include <vector>

#include <libbf/login_cookie.hpp>

namespace libbf {
typedef std::vector<class download> downloads_t;
class download {
  public:
    std::string name;
    std::uint32_t download_number;
    std::uint32_t image_number;
    bool m4b_available;
    std::vector<std::pair<std::string, int>> supplementary_media;

    download(std::string name, std::uint32_t image_number, std::uint32_t download_number,
             bool m4b_available, std::vector<std::pair<std::string, int>> supplementary_media)
            : name(name), download_number(download_number), image_number(image_number),
              m4b_available(m4b_available), supplementary_media(supplementary_media) {}
    download() = default;

    std::filesystem::path download_mp3(
            libbf::login_cookie& cookie,
            std::function<bool(size_t, size_t, size_t, size_t)> progress_callback =
                    [](size_t, size_t, size_t, size_t) { return true; });

    std::filesystem::path download_m4b(
            libbf::login_cookie& cookie,
            std::function<bool(size_t, size_t, size_t, size_t)> progress_callback =
                    [](size_t, size_t, size_t, size_t) { return true; });

    std::pair<std::filesystem::path, std::string> download_extra(
            std::pair<std::string, int> extra, libbf::login_cookie& cookie,
            std::function<bool(size_t, size_t, size_t, size_t)> progress_callback =
                    [](size_t, size_t, size_t, size_t) { return true; });

    static downloads_t get_downloads(login_cookie& cookie);
};

} // namespace libbf
