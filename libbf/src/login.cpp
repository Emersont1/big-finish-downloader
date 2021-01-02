#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <cpr/cpr.h>
#include <cpr/payload.h>

#include <libbf/exceptions.hpp>
#include <libbf/login_cookie.hpp>

libbf::login_cookie libbf::login_cookie::login(std::string email,
                                               std::string password,
                                               bool        remember_me) {

  cpr::Response r = cpr::Post(
      cpr::Url{"https://www.bigfinish.com/customers/login"},
      cpr::Payload{{"_method", "POST"},
                   {"data%5Bpost_action%5D", "login"},
                   {"data%5BCustomer%5D%5Bemail_address%5D", email},
                   {"data%5BCustomer%5D%5Bpassword%5D", password},
                   {"data%5Bremember_me%5D", remember_me ? "1" : "0"}});

  if (r.text.find("You have successfully logged in.") == std::string::npos)
    throw libbf::login_failed_exception();

  auto a = libbf::login_cookie(email, r.cookies["CakeCookie[Customer]"],
                               r.cookies["CAKEPHP"]);
  return a;
}

libbf::login_cookie libbf::login_cookie::example() {
  auto a = libbf::login_cookie("the_doctor@tardis.vortex",
                               "long cookie of lots of random stuff",
                               "short cookie");
  return a;
}