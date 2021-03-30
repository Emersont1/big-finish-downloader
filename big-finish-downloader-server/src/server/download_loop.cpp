#include <libbf/server/server.hpp>

#include <cmath>
#include <fstream>

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>

#include <utils.hpp>
#include <zip_helper.hpp>

using namespace std::chrono_literals;

void libbf::server::server::download_loop() {
    auto progress_callback = [&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal,
                                 size_t uploadNow) {
        progress = (double) downloadNow / std::max(downloadTotal, 1ul);
        if (close)
            spdlog::info("Cancelled Download");
        return !close;
    };
    auto unzip_callback = [&](size_t num, size_t den) {
        progress = (double) num / std::max(den, 1ul);
        if (close)
            spdlog::info("Cancelled Unzip");
        return !close;
    };


    while (!close) {
        std::cout << "loop!" << std::endl;
        {
            std::cout << "writing file" << std::endl;
            std::ofstream out;
            out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                out.open(dest_path / "data.json");
                std::cout << (dest_path / "data.json").string() << std::endl;
                nlohmann::json j;
                j["ids"] = downloaded_ids;

                std::vector<libbf::login_cookie> _logins;
                std::transform(logins.begin(), logins.end(), std::back_inserter(_logins),
                               [](std::shared_ptr<libbf::login_cookie> c) -> libbf::login_cookie {
                                   return *c;
                               });
                j["logins"] = _logins;
                out << j;
                out.close();
            } catch (std::ifstream::failure e) {
                std::cout << "Exception opening/reading/closing file" << std::endl;
                std::cout << e.what() << std::endl;
            }
        }
        if (download_queue.size() == 0) {
            std::this_thread::sleep_for(5s);
            continue;
        }

        auto x = download_queue.pop();
        auto& value = x.first;
        auto& cookie = x.second;

        status_i = "Downloading item " + value.name;
        img_number = value.image_number;
        spdlog::info(status_i);

        std::string _name = replace_all(value.name, ": ", "/");
        std::string name = replace_all(_name, " - ", "/");
        std::filesystem::create_directories(dest_path / name);
        if (value.m4b_available) {
            status_ii = "Downloading Main Feature";
            spdlog::info(status_ii);
            auto path = value.download_m4b(*cookie, progress_callback);
            status_ii = "Extracting Main Feature";
            spdlog::info(status_ii);
            helper::extract_zip(dest_path / name, path, unzip_callback);
            std::filesystem::remove(path);
        } else {
            status_ii = "Downloading Main Feature";
            spdlog::info(status_ii);
            auto path = value.download_mp3(*cookie, progress_callback);
            status_ii = "Extracting Main Feature";
            spdlog::info(status_ii);

            helper::extract_zip(dest_path / name, path, unzip_callback);
            std::filesystem::remove(path);
        }

        spdlog::info(value.supplementary_media.size() > 0 ? "Downloading Bonus Features"
                                                          : "No Bonus Features To Download");

        for (auto bonus : value.supplementary_media) {
            status_ii = "Downloading Additional Feature - " + bonus.first;
            spdlog::info(status_ii);
            auto res = value.download_extra(bonus, *cookie, progress_callback);

            spdlog::info("downloaded file with MIME type {}", res.second);

            if (res.second == "zip") {
                status_ii = "Extracting Bonus Feature";
                spdlog::info(status_ii);
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
        spdlog::info((dest_path / name / "cover.jpg").string());
        std::ofstream of(dest_path / name / "cover.jpg", std::ios::binary);
        cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com/image/release/" +
                                            std::to_string(value.image_number) + "/large.jpg"});
        of.write(r.text.c_str(), r.text.size());
        of.close();

        downloaded_ids.insert(value.image_number);
    }
}
