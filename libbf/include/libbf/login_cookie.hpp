#pragma once

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

namespace libbf {
class login_cookie {
    std::string token;

  public:
    login_cookie() = default;
    login_cookie(std::string token) : token(token) {}
    bool valid();

    static login_cookie login(std::string email, std::string password, bool remember_me = true);

    friend std::ostream& operator<<(std::ostream& os, const login_cookie& l);
    std::string get_token() {
        return token;
    }
};

inline std::ostream& operator<<(std::ostream& os, const login_cookie& l) {
    os << l.token;
    return os;
}

} // namespace libbf