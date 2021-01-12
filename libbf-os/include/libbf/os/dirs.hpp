#pragma once

#include <filesystem>

namespace libbf::os {
std::filesystem::path get_cache();
std::filesystem::path get_home();
std::string file_prefix();
} // namespace libbf::os