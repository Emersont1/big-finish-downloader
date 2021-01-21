#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <mime.h>

#include <utils.hpp>
#include <libbf/gui/modules/main_window.hpp>
#include <zip_helper.hpp>

int libbf::gui::main_window::download(libbf::download value, std::shared_future<void> v) {
    auto progress_callback = [&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal,
                                 size_t uploadNow) {
        download_progress.store((double) downloadNow / (downloadTotal + 1));
        return v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout;
    };
    auto unzip_callback = [&](size_t num, size_t den) {
        download_progress.store((double) num / (den + 1));
        return v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout;
    };

    if (value.m4b_available && settings.get_prefer_m4b()) {
        status_ii = "Downloading Main Feature";
        auto path = value.download_m4b(cookie, progress_callback);
        status_ii = "Extracting Main Feature";
        helper::extract_zip(settings.get_path(), path, unzip_callback);
        std::filesystem::remove(path);
    } else if (settings.get_fallback_mp3() || !settings.get_prefer_m4b()) {
        status_ii = "Downloading Main Feature";
        auto path = value.download_mp3(cookie, progress_callback);
        status_ii = "Extracting Main Feature";
        helper::extract_zip(settings.get_path(), path, unzip_callback);
        std::filesystem::remove(path);
    }
    if (settings.get_download_extras()) {
        for (auto bonus : value.supplementary_media) {
            status_ii = "Downloading Additional Feature - " + bonus.first;
            auto res = value.download_extra(bonus, cookie, progress_callback);
            if (mime::extension(res.second) == "zip") {
                status_ii = "Extracting Bonus Feature - " + bonus.first;
                helper::extract_zip(settings.get_path(), res.first, unzip_callback);

            } else {
                std::string name = replace_all(value.name, ": ", " - ");
                auto p = settings.get_path() / name /
                         (bonus.first + "." + mime::extension(res.second));
                std::filesystem::create_directories(p.parent_path());
                std::filesystem::copy_file(res.first, p);
            }
            std::filesystem::remove(res.first);
            status_ii = "";
        }
    }

    return value.image_number;
}