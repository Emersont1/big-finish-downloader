#include <iostream>
#include <libbf/os/dirs.hpp>
#include <subprocess.hpp>

std::filesystem::path libbf::os::get_cache() {
    return std::filesystem::path(std::getenv("HOME")) / ".cache" / "big-finish";
}

std::filesystem::path libbf::os::get_home() {
    return std::filesystem::path(std::getenv("HOME"));
}

std::filesystem::path libbf::os::get_music() {
    subprocess::popen cmd("xdg-user-dir", {"MUSIC"});

    int ret = cmd.wait();
    if (ret == 0) {
        std::string path;
        cmd.stdout() >> path;
        return std::filesystem::path(path);
    } else {
        return libbf::os::get_home() / "Music";
    }
}

std::string libbf::os::file_prefix() {
    return "file://";
}