#pragma once

#include <atomic>
#include <filesystem>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <atomic_queue.hpp>
#include <libbf/downloads.hpp>
#include <libbf/login_cookie.hpp>

namespace libbf::server {
class server {
    std::thread download_thread;
    std::atomic<bool> close;
    utils::atomic_queue<std::pair<libbf::download, std::shared_ptr<libbf::login_cookie>>>
            download_queue;

    // A list of IDs and wether or not they have been processed (added to queue and downloaded) or
    // not;
    std::vector<bool> processed_ids;

    // list of login_cookies
    std::vector<std::shared_ptr<libbf::login_cookie>> logins;

    void download_loop();
    std::filesystem::path dest_path = std::filesystem::current_path() / "Music";

  public:
    server();
    void add_login(libbf::login_cookie);
    void refresh_downloads();
};
} // namespace libbf::server