#pragma once

#include <string>

#include <libbf/login_cookie.hpp>

namespace libbf::gui {
void                store(libbf::login_cookie);
libbf::login_cookie retrieve();
} // namespace libbf::gui