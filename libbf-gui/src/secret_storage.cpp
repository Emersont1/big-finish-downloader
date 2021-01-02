#include <iostream>

#include <libbf/gui/secret_storage.hpp>

#include <libsecret/secret.h>

const SecretSchema * cookie_schema(void) G_GNUC_CONST;

void libbf::gui::store(libbf::login_cookie l) {
  GError * error = nullptr;

  secret_password_store_sync(
      cookie_schema(), SECRET_COLLECTION_DEFAULT, "Big Finish Login",
      l.get_customer().c_str(), nullptr, &error, "CakePHP",
      l.get_cakephp().c_str(), "email", l.get_email().c_str(), nullptr);

  if (error != NULL) {
    /* ... handle the failure here */
    std::cout << "store failed" << std::endl;
    g_error_free(error);
  } else {
    /* ... do something now that the password has been stored */
    std::cout << "store successful" << std::endl;
  }
}
