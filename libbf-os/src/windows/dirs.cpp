#include <iostream>
#include <libbf/os/dirs.hpp>

#include <ShlObj_core.h>

std::filesystem::path libbf::os::get_cache() {
    return std::filesystem::path(std::getenv("LOCALAPPDATA")) / "big-finish";
}

std::filesystem::path libbf::os::get_home() {
    return std::filesystem::path(std::getenv("USERPROFILE"));
}

std::filesystem::path libbf::os::get_music() {
    std::string music_path("\0", _MAX_PATH);

    if (SHGetSpecialFolderPath(nullptr, music_path.data(), CSIDL_MYMUSIC, true)) {
        return std::filesystem::path(music_path);
    }
    return libbf::os::get_home() / "Music";
}

std::string libbf::os::file_prefix() {
    return "explorer.exe ";
}