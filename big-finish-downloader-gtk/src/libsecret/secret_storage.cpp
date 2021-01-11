#include <iostream>

#include <libbf/gui/exceptions.hpp>
#include <libbf/gui/secret_storage.hpp>

#include <libsecret/secret.h>

const SecretSchema* cookie_schema(void) G_GNUC_CONST;

void libbf::gui::store(libbf::login_cookie l) {
    /*GError* error = nullptr;
    nlohmann::json j = l;
    secret_password_store_sync(cookie_schema(), SECRET_COLLECTION_DEFAULT, "Big Finish Login",
                               j.dump().c_str(), nullptr, &error, "site", "bigfinish.com", nullptr);

    if (error != nullptr) {
        g_error_free(error);
        throw libbf::gui::secret_write_failed_exception();
    }*/
}

libbf::login_cookie libbf::gui::retrieve() {
    return libbf::login_cookie("example");
}

void libbf::gui::revoke() {
    GError* error = nullptr;
    secret_password_clear_sync(cookie_schema(), nullptr, &error, "site", "bigfinish.com", nullptr);
}