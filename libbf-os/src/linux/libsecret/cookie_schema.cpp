#include <libbf/os/secret_storage.hpp>

#include <libsecret/secret.h>

const SecretSchema* cookie_schema(void) G_GNUC_CONST;

const SecretSchema* cookie_schema(void) {
    static const SecretSchema the_schema = {"uk.et1.big-finish.login",
                                            SECRET_SCHEMA_NONE,
                                            {
                                                    {"site", SECRET_SCHEMA_ATTRIBUTE_STRING},
                                                    {"NULL", SECRET_SCHEMA_ATTRIBUTE_STRING},
                                            }};
    return &the_schema;
}