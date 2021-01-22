#include <libbf/server/server.hpp>

#include <fstream>

#include <spdlog/spdlog.h>
#include <cpr/cpr.h>

#include <utils.hpp>
#include <zip_helper.hpp>

using namespace std::chrono_literals;

void libbf::server::server::download_loop() {
    auto progress_callback = [&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal,
                                 size_t uploadNow) {
        if (close)
            spdlog::info("Cancelled Download");
        return !close;
    };
    auto unzip_callback = [&](size_t num, size_t den) {
        if (close)
            spdlog::info("Cancelled Unzip");
        return !close;
    };


    while (!close) {
        std::cout << "loop!" << std::endl;
        if (download_queue.size() == 0) {
            std::this_thread::sleep_for(5s);
            continue;
        }

        auto x = download_queue.pop();
        auto& value = x.first;
        auto& cookie = x.second;
        
        std::string name = replace_all(value.name, ": ", " - ");

        if (value.m4b_available) {
            spdlog::info("Downloading Main Feature");
            auto path = value.download_m4b(*cookie, progress_callback);
            spdlog::info("Extracting Main Feature");
            helper::extract_zip(dest_path, path, unzip_callback);
            std::filesystem::remove(path);
        } else {
            spdlog::info("Downloading Main Feature");
            auto path = value.download_mp3(*cookie, progress_callback);
            spdlog::info("Extracting Main Feature");

            helper::extract_zip(dest_path, path, unzip_callback);
            std::filesystem::remove(path);
        }

        spdlog::info(value.supplementary_media.size() > 0 ? "Downloading Bonus Features"
                                                          : "No Bonus Features To Download");

        for (auto bonus : value.supplementary_media) {
            spdlog::info("Downloading Additional Feature - {}", bonus.first);
            auto res = value.download_extra(bonus, *cookie, progress_callback);

            spdlog::info("downloaded file with MIME type {}", res.second);

            if (res.second == "zip") {
                spdlog::info("Extracting Bonus Feature");
                auto p = dest_path / name;
                std::filesystem::create_directories(p);
                helper::extract_zip(p, res.first, unzip_callback);

            } else {
                std::string dot = bonus.first.back() == '.' ? "" : ".";
                auto p = dest_path / name / (bonus.first + dot + res.second);
                spdlog::info("Saving to path {}", p.string());
                std::filesystem::create_directories(p.parent_path());
                if (std::filesystem::exists(p))
                    std::filesystem::remove(p);
                std::filesystem::copy_file(res.first, p);
            }
            std::filesystem::remove(res.first);
        }

        // Download Cover JPG
            std::ofstream of(dest_path / name /+ "cover.jpg", std::ios::binary);
            cpr::Response r = cpr::Get(
                    cpr::Url{"https://www.bigfinish.com/image/release/" + std::to_string(value.image_number) + "/large.jpg"});
            of.write(r.text.c_str(), r.text.size());
            of.close();
    }
}