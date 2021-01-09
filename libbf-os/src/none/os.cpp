#include <libbf/os/dirs.hpp>
#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>
#include <libbf/os/settings.hpp>

libbf::os::settings::settings() {}

bool libbf::os::settings::get_prefer_m4b() {
    return true;
}

void libbf::os::settings::set_prefer_m4b(bool x) {}

bool libbf::os::settings::get_fallback_mp3() {
    return true;
}

void libbf::os::settings::set_fallback_mp3(bool x) {}

bool libbf::os::settings::get_download_extras() {
    return true;
}

void libbf::os::settings::set_download_extras(bool x) {}

std::filesystem::path libbf::os::settings::get_path() {
    return std::filesystem::current_path();
}

void libbf::os::settings::set_path(std::filesystem::path x) {}


void libbf::os::store(libbf::login_cookie l) {
    throw libbf::os::secret_write_failed_exception();
}

libbf::login_cookie libbf::os::retrieve() {
    throw libbf::os::secret_not_found_exception();
}

void libbf::os::revoke() {}

std::filesystem::path libbf::os::get_cache() {
    return std::filesystem::current_path();
}