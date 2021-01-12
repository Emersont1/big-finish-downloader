#include <iostream>
#include <libbf/os/dirs.hpp>

std::filesystem::path libbf::os::get_cache() {
    return std::filesystem::path(std::getenv("HOME")) / ".cache" / "big-finish";
}

std::filesystem::path libbf::os::get_home() {
    return std::filesystem::path(std::getenv("HOME"));
}

std::string libbf::os::file_prefix() {
    return "file://";
}