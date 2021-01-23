#include <libbf/server/server.hpp>

#include <spdlog/spdlog.h>

#include <utils.hpp>
#include <zip_helper.hpp>

libbf::server::server::server()
        : close(false), download_thread(&libbf::server::server::download_loop, this) {
    // load items from file or something
}