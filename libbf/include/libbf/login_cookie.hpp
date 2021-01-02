#pragma once

#include <iostream>
#include <string>

namespace libbf {
class login_cookie {
  std::string email;
  std::string cakephp_value;
  std::string customer_value;

public:
  static login_cookie   login(std::string email, std::string password,
                              bool remember_me = true);
  friend std::ostream & operator<<(std::ostream & os, const login_cookie & l);
  std::string           get_cakephp() { return cakephp_value; }
  std::string           get_customer() { return customer_value; }
  std::string           get_email() { return email; }

  [[deprecated("Should only be used for testing")]] static login_cookie
  example();
};

inline std::ostream & operator<<(std::ostream & os, const login_cookie & l) {
  os << "{Email: \"" << l.email << "\", CakePHP: \"" << l.cakephp_value
     << "\"; Customer: \"" << l.customer_value << "\"}";
  return os;
}

} // namespace libbf