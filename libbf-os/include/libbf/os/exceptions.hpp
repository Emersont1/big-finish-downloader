#pragma once
#include <stdexcept>

namespace libbf::os {
class secret_not_found_exception : public std::runtime_error {
  public:
    secret_not_found_exception() : std::runtime_error("Secret not found in keyring") {}
};

class secret_write_failed_exception : public std::runtime_error {
  public:
    secret_write_failed_exception() : std::runtime_error("Secret Write Failed!") {}
};
} // namespace libbf::os