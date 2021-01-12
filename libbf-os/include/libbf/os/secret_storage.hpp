#pragma once

#include <string>

#include <libbf/login_cookie.hpp>

namespace libbf::os {
void store(libbf::login_cookie);
libbf::login_cookie retrieve();
void revoke();
} // namespace libbf::os