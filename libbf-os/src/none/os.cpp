#include <libbf/os/dirs.hpp>
#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>
#include <libbf/os/settings.hpp>

libbf::os::settings::settings() {}

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