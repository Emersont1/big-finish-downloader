#include <memory>
#include <vector>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


namespace libbf {
void register_logger_default(std::shared_ptr<spdlog::logger>);
}