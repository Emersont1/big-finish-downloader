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

  cpr::Response r =
      cpr::Post(cpr::Url{"https://www.bigfinish.com/customers/login"},
                cpr::Payload{{"_method", "POST"},
                             {"data[post_action]", "login"},
                             {"data[Customer][email_address]", email},
                             {"data[Customer][password]", password},
                             {"data[remember_me]", "1"}});

  if (r.text.find("You have successfully logged in.") == std::string::npos)
    throw libbf::login_failed_exception();

  auto a = libbf::login_cookie(email, r.cookies["CAKEPHP"],
                               r.cookies["CakeCookie[Customer]"]);
  return a;
}

libbf::login_cookie libbf::login_cookie::example() {
  auto a = libbf::login_cookie("the_doctor@tardis.vortex",
                               "long cookie of lots of random stuff",
                               "short cookie");
  return a;
}

bool libbf::login_cookie::valid() {
  cpr::Response r =
      cpr::Get(cpr::Url{"https://www.bigfinish.com/customers/my_account/"},
               cpr::Cookies{{"CakeCookie[Customer]", customer_value},
                            {"CAKEPHP", cakephp_value}});
  return r.status_code == 200;
}