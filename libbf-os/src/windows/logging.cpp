#include <libbf/logging.hpp>
#include <libbf/os/logging.hpp>

void libbf::os::register_logger_default(std::shared_ptr<spdlog::logger> l) {
    spdlog::register_logger(l);
    spdlog::set_default_logger(l);
    libbf::register_logger_default(l);
}