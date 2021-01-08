#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <cpr/cpr.h>
#include <cpr/payload.h>

#include <libbf/exceptions.hpp>
#include <libbf/login_cookie.hpp>

libbf::login_cookie libbf::login_cookie::login(std::string email, std::string password,
                                               bool remember_me) {
    cpr::Response r = cpr::Post(cpr::Url{"https://www.bigfinish.com/apiv3/login.json"},
                                cpr::Payload{
                                        {"data[Customer][email_address]", email},
                                        {"data[Customer][password]", password},
                                });

    nlohmann::json j = nlohmann::json::parse(r.text);

    if (j.contains("login_failed") && j["login_failed"].get<bool>())
        throw libbf::login_failed_exception();

    auto a = libbf::login_cookie(j["Customer"]["token"].get<std::string>());
    return a;
}

bool libbf::login_cookie::valid() {
    return false;
}