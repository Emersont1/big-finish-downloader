#include <iostream>

#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>

#include <libsecret/secret.h>

const SecretSchema* cookie_schema(void) G_GNUC_CONST;

void libbf::os::store(libbf::login_cookie l) {
    GError* error = nullptr;
    nlohmann::json j = l;
    secret_password_store_sync(cookie_schema(), SECRET_COLLECTION_DEFAULT, "Big Finish Login",
                               j.dump().c_str(), nullptr, &error, "site", "bigfinish.com", nullptr);

    if (error != nullptr) {
        g_error_free(error);
        throw libbf::os::secret_write_failed_exception();
    }
}

libbf::login_cookie libbf::os::retrieve() {
    GError* error = nullptr;

    /* The attributes used to lookup the password should conform to the schema. */
    gchar* password = secret_password_lookup_sync(cookie_schema(), nullptr, &error, "site",
                                                  "bigfinish.com", nullptr);

    if (error != nullptr) {
        /* ... handle the failure here */
        g_error_free(error);
        throw libbf::os::secret_not_found_exception();

    } else if (password == nullptr) {
        throw libbf::os::secret_not_found_exception();

    } else {
        auto j = nlohmann::json::parse((char*) password);

        secret_password_free(password);
        return j;
    }
}

void libbf::os::revoke() {
    GError* error = nullptr;
    secret_password_clear_sync(cookie_schema(), nullptr, &error, "site", "bigfinish.com", nullptr);
}