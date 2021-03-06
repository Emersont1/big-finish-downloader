#include <gio/gio.h>

#include <libbf/os/dirs.hpp>
#include <libbf/os/settings.hpp>

libbf::os::settings::settings() {
    data = (void*) g_settings_new("uk.et1.big-finish");
}

bool libbf::os::settings::get_prefer_m4b() {
    return g_settings_get_boolean((GSettings*) data, "prefer-m4b");
}

void libbf::os::settings::set_prefer_m4b(bool x) {
    g_settings_set_boolean((GSettings*) data, "prefer-m4b", x);
}

bool libbf::os::settings::get_fallback_mp3() {
    return g_settings_get_boolean((GSettings*) data, "fallback-mp3");
}

void libbf::os::settings::set_fallback_mp3(bool x) {
    g_settings_set_boolean((GSettings*) data, "fallback-mp3", x);
}

bool libbf::os::settings::get_download_extras() {
    return g_settings_get_boolean((GSettings*) data, "download-extras");
}

void libbf::os::settings::set_download_extras(bool x) {
    g_settings_set_boolean((GSettings*) data, "download-extras", x);
}

bool libbf::os::settings::get_download_automatically() {
    return g_settings_get_boolean((GSettings*) data, "download-automatically");
}

void libbf::os::settings::set_download_automatically(bool x) {
    g_settings_set_boolean((GSettings*) data, "download-automatically", x);
}

std::filesystem::path libbf::os::settings::get_path() {
    auto x = std::string(g_settings_get_string((GSettings*) data, "download-directory"));
    if (x != "")
        return x;
    return libbf::os::get_music();
}

void libbf::os::settings::set_path(std::filesystem::path x) {
    auto path = x.string();
    g_settings_set_string((GSettings*) data, "download-directory", path.c_str());
}
