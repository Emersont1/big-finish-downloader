#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <cpr/cpr.h>
#include <cpr/payload.h>

#include <libbf/exceptions.hpp>
#include <libbf/login_cookie.hpp>

std::string url_encode(std::string & value) {
  std::ostringstream escaped;
  escaped.fill('0');
  escaped << std::hex;

  for (auto c : value) {

    // Keep alphanumeric and other accepted characters intact
    if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      escaped << c;
      continue;
    }

    // Any other characters are percent-encoded
    escaped << std::uppercase;
    escaped << '%' << std::setw(2) << int((unsigned char) c);
    escaped << std::nouppercase;
  }

  return escaped.str();
}

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

  auto a = libbf::login_cookie();
  a.customer_value = r.cookies["CakeCookie[Customer]"];
  a.cakephp_value = r.cookies["CAKEPHP"];
  return a;
}