#include <libbf/logging.hpp>

void libbf::register_logger_default(std::shared_ptr<spdlog::logger> l) {
    spdlog::register_logger(l);
    spdlog::set_default_logger(l);
}