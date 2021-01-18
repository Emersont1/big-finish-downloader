#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <cpr/cpr.h>
#include <cpr/payload.h>

#include <spdlog/spdlog.h>

#include <libbf/exceptions.hpp>
#include <libbf/login_cookie.hpp>

libbf::login_cookie libbf::login_cookie::login(std::string email, std::string password,
                                               bool remember_me) {
    cpr::Response r = cpr::Post(cpr::Url{"https://www.bigfinish.com/customers/login"},
                                cpr::Payload{{"_method", "POST"},
                                             {"data%5BCustomer%5D%5Bemail_address%5D", email},
                                             {"data%5BCustomer%5D%5Bpassword%5D", password},
                                             {"data%5Bremember_me%5D", "1"}});

    spdlog::info("Login: Got Status Code: {}", r.status_code);
    if (r.status_code != 200) {
        spdlog::warn(r.error.message);
    }

    if (r.text.find("You have successfully logged in.") == std::string::npos)
        throw libbf::login_failed_exception();

    auto a = libbf::login_cookie(email, r.cookies["CAKEPHP"], r.cookies["CakeCookie[Customer]"]);
    return a;
}

libbf::login_cookie libbf::login_cookie::example() {
    auto a = libbf::login_cookie("the_doctor@tardis.vortex", "long cookie of lots of random stuff",
                                 "short cookie");
    return a;
}

bool libbf::login_cookie::valid() {
    cpr::Response r = cpr::Get(
            cpr::Url{"https://www.bigfinish.com/customers/my_account/"},
            cpr::Cookies{{"CakeCookie[Customer]", customer_value}, {"CAKEPHP", cakephp_value}});
    spdlog::info("Got Status Code: {}", r.status_code);
    return r.status_code == 200;
}