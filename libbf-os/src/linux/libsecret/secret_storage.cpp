#include <iostream>

#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>

#include <spdlog/spdlog.h>

#include <libsecret/secret.h>

const SecretSchema* cookie_schema(void) G_GNUC_CONST;

void libbf::os::store(libbf::login_cookie l) {
    GError* error = nullptr;
    nlohmann::json j = l;
    secret_password_store_sync(cookie_schema(), SECRET_COLLECTION_DEFAULT, "Big Finish Login",
                               j.dump().c_str(), nullptr, &error, "version", "1", "email",
                               l.get_email().c_str(), nullptr);

    if (error != nullptr) {
        g_error_free(error);
        throw libbf::os::secret_write_failed_exception();
    }
}

libbf::login_cookie libbf::os::retrieve() {
    spdlog::info("retrieving secret");

    GError* error = nullptr;

    /* The attributes used to lookup the password should conform to the schema. */
    GList* secret = secret_password_search_sync(cookie_schema(), SECRET_SEARCH_NONE, nullptr,
                                                &error, "version", "1", nullptr);

    if (error != nullptr) {
        /* ... handle the failure here */
        g_error_free(error);
        throw libbf::os::secret_not_found_exception();

    } else if (secret == nullptr) {
        throw libbf::os::secret_not_found_exception();

    } else {
        auto retrievable = SECRET_RETRIEVABLE(secret->data);
        auto value = secret_retrievable_retrieve_secret_sync(retrievable, nullptr, &error);
        if (error != nullptr) {
            /* ... handle the failure here */
            g_error_free(error);
            throw libbf::os::secret_not_found_exception();
        }
        if (value == nullptr) {
            throw libbf::os::secret_not_found_exception();
        }
        gsize length;
        auto pass = secret_value_get(value, &length);
        std::string secret_json(pass);

        auto attr = secret_retrievable_get_attributes(retrievable);
        std::string email((char*) g_hash_table_lookup(attr, "email"));

        auto j = nlohmann::json::parse(secret_json);

        g_list_free(secret);
        return j;
    }
}

void libbf::os::revoke() {
    GError* error = nullptr;
    spdlog::info("revoke called");
    secret_password_clear_sync(cookie_schema(), nullptr, &error, "version", "1", nullptr);
}