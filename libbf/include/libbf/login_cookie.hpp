#pragma once

#include <string>

namespace libbf {
class login_cookie {
  std::string cookie_value;

public:
  static login_cookie   login(std::string email, std::string password,
                              bool remember_me = true);
  friend std::ostream & operator<<(std::ostream & os, const login_cookie & l);
};

inline std::ostream & operator<<(std::ostream & os, const login_cookie & l) {
  os << "{Cookie Value: \"" << l.cookie_value << "\"}";
  return os;
}

} // namespace libbf