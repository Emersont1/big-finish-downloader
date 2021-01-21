#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <mime.h>

#include <spdlog/spdlog.h>

#include <libbf/gui/modules/main_window.hpp>
#include <utils.hpp>
#include <zip_helper.hpp>

int libbf::gui::main_window::download(libbf::download value, std::shared_future<void> v) {
    spdlog::info("Downloading item \"{}\"", value.name);
    auto progress_callback = [&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal,
                                 size_t uploadNow) {
        download_progress.store((double) downloadNow / (downloadTotal + 1));
        auto a = v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout;
        if (!a)
            spdlog::info("Cancelled Download");
        return a;
    };
    auto unzip_callback = [&](size_t num, size_t den) {
        download_progress.store((double) num / (den + 1));
        auto a = v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout;
        if (!a)
            spdlog::info("Cancelled Download");
        return a;
    };

    if (value.m4b_available && settings.get_prefer_m4b()) {
        spdlog::info("Downloading Main Feature");
        status_ii = "Downloading Main Feature";
        auto path = value.download_m4b(cookie, progress_callback);
        status_ii = "Extracting Main Feature";
        spdlog::info("Extracting Main Feature");
        helper::extract_zip(settings.get_path(), path, unzip_callback);
        std::filesystem::remove(path);
    } else if (settings.get_fallback_mp3() || !settings.get_prefer_m4b()) {
        spdlog::info("Downloading Main Feature");
        status_ii = "Downloading Main Feature";
        auto path = value.download_mp3(cookie, progress_callback);
        spdlog::info("Extracting Main Feature");

        status_ii = "Extracting Main Feature";
        helper::extract_zip(settings.get_path(), path, unzip_callback);
        std::filesystem::remove(path);
    }
    if (settings.get_download_extras()) {
        spdlog::info(value.supplementary_media.size() > 0 ? "Downloading Bonus Features"
                                                          : "No Bonus Features To Download");

        for (auto bonus : value.supplementary_media) {
            spdlog::info("Downloading Additional Feature - {}", bonus.first);
            status_ii = "Downloading Additional Feature - " + bonus.first;
            auto res = value.download_extra(bonus, cookie, progress_callback);

            spdlog::info("downloaded file with MIME type {}", res.second);
            if (mime::extension(res.second) == "zip") {
                spdlog::info("Extracting Bonus Feature");
                status_ii = "Extracting Bonus Feature - " + bonus.first;
                helper::extract_zip(settings.get_path(), res.first, unzip_callback);

            } else {
                std::string name = replace_all(value.name, ": ", " - ");
                auto p = settings.get_path() / name /
                         (bonus.first + "." + mime::extension(res.second));
                spdlog::info("Saving to path {}", p.string());
                std::filesystem::create_directories(p.parent_path());
                if (std::filesystem::exists(p))
                    std::filesystem::remove(p);
                std::filesystem::copy_file(res.first, p);
            }
            std::filesystem::remove(res.first);
            status_ii = "";
        }
    }

    return value.image_number;
}