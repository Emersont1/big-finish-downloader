#pragma once

#include <filesystem>

namespace libbf::os {
class settings {
    // data pointer to settings object (os dependant on what it holds)
    void* data;

  public:
    settings();
    bool get_prefer_m4b();
    void set_prefer_m4b(bool);
    bool get_fallback_mp3();
    void set_fallback_mp3(bool);
    bool get_download_extras();
    void set_download_extras(bool);
    bool get_download_automatically();
    void set_download_automatically(bool);

    std::filesystem::path get_path();
    void set_path(std::filesystem::path);
};
} // namespace libbf::os
