#pragma once
#include <stdexcept>

namespace libbf {
class login_failed_exception : public std::runtime_error {
public:
  login_failed_exception() : std::runtime_error("Login Failed") {}
};

class parse_failed_exception : public std::runtime_error {
public:
  parse_failed_exception() : std::runtime_error("Parse Failed") {}
};
} // namespace libbf