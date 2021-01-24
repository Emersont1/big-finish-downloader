#include <libbf/server/server.hpp>

#include <spdlog/spdlog.h>

#include <utils.hpp>
#include <zip_helper.hpp>

void libbf::server::server::refresh_downloads() {
    for (size_t i = 0; i < logins.size();) {
        if (logins[i]->valid()) {
            auto ds = libbf::download::get_downloads(*logins[i]);
            for (auto& download : ds) {
                if (!processed_ids.count(download.image_number)) {
                    processed_ids.insert(download.image_number);
                    download_queue.push(std::make_pair(download, logins[i]));
                }
            }
            i++;
        } else {
            logins.erase(logins.begin() + i);
        }
    }
}

void libbf::server::server::add_login(libbf::login_cookie cookie) {
    logins.push_back(std::make_shared<libbf::login_cookie>(cookie));
}

std::vector<std::pair<libbf::download, std::shared_ptr<libbf::login_cookie>>>
libbf::server::server::get_queue() {
    return download_queue.elements();
}

std::tuple<double, std::string, std::string, int> libbf::server::server::get_status() {
    return std::make_tuple(progress, status_i, status_ii, img_number);
}