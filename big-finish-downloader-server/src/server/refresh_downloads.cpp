#include <libbf/server/server.hpp>

#include <spdlog/spdlog.h>

#include <utils.hpp>
#include <zip_helper.hpp>
bool vector_at_safe(std::vector<bool>& data, size_t index) {
    try {
        return data.at(index);
    } catch (std::out_of_range) {
        data.resize(index);
        return false;
    }
}
void libbf::server::server::refresh_downloads() {
    for (auto& cookie : logins) {
        auto ds = libbf::download::get_downloads(*cookie);
        for (auto& download : ds) {
            if (!vector_at_safe(processed_ids, download.image_number)) {
                processed_ids[download.image_number] = true;
                download_queue.push(std::make_pair(download, cookie));
            }
        }
    }
}

void libbf::server::server::add_login(libbf::login_cookie cookie) {
    logins.push_back(std::make_shared<libbf::login_cookie>(cookie));
}