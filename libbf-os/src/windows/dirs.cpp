#include <iostream>
#include <libbf/os/dirs.hpp>

std::filesystem::path libbf::os::get_cache() {
    return std::filesystem::path(std::getenv("LOCALAPPDATA")) / "big-finish";
}

std::filesystem::path libbf::os::get_home() {
    return std::filesystem::path(std::getenv("USERPROFILE"));
}

std::filesystem::path libbf::os::get_music() {
    return std::filesystem::path(std::getenv("CSIDL_MYMUSIC"));
}

std::string libbf::os::file_prefix() {
    return "explorer.exe ";
}