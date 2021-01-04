#pragma once

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

namespace libbf {
class login_cookie {
    std::string email;
    std::string cakephp_value;
    std::string customer_value;

  public:
    login_cookie() = default;
    login_cookie(std::string email, std::string cakephp_value, std::string customer_value)
            : email(email), cakephp_value(cakephp_value), customer_value(customer_value) {}
    bool valid();

    static login_cookie login(std::string email, std::string password, bool remember_me = true);

    friend std::ostream& operator<<(std::ostream& os, const login_cookie& l);
    friend void to_json(nlohmann::json& j, const login_cookie& r);
    friend void from_json(const nlohmann::json& j, login_cookie& r);
    std::string get_cakephp() {
        return cakephp_value;
    }
    std::string get_customer() {
        return customer_value;
    }
    std::string get_email() {
        return email;
    }

    [[deprecated("Should only be used for testing")]] static login_cookie example();
};

inline std::ostream& operator<<(std::ostream& os, const login_cookie& l) {
    os << "{Email: \"" << l.email << "\", CakePHP: \"" << l.cakephp_value << "\"; Customer: \""
       << l.customer_value << "\"}";
    return os;
}

inline void to_json(nlohmann::json& j, const login_cookie& r) {
    j = nlohmann::json{
            {"email", r.email},
            {"cakephp", r.cakephp_value},
            {"customer", r.customer_value},
    };
}

inline void from_json(const nlohmann::json& j, login_cookie& p) {
    j.at("email").get_to(p.email);
    j.at("cakephp").get_to(p.cakephp_value);
    j.at("customer").get_to(p.customer_value);
}

} // namespace libbf