#include <iostream>

#include <cpr/cpr.h>
#include <tinyxml2.h>
#include <ext/tixml2ex.h>

#include <libbf/downloads.hpp>

std::vector<libbf::download>
libbf::download::get_downloads(libbf::login_cookie & cookie) {
  cpr::Response r =
      cpr::Get(cpr::Url{"https://www.bigfinish.com/customers/my_account/"},
               cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                            {"CAKEPHP", cookie.get_cakephp()}});

  tinyxml2::XMLDocument doc;
  doc.Parse(r.text.c_str());
  //std::cout << r.text << std::endl;
  {
          tinyxml2::XMLPrinter printer;
    doc.Accept( &printer );
    std::cout << printer.CStr()<<std::endl;
  }
for (tinyxml2::XMLElement* part : tinyxml2::tixml2ex::selection (doc, "//div[@class='item account-release-download']")){
    tinyxml2::XMLPrinter printer;
    part->Accept( &printer );
    std::cout << printer.CStr()<<std::endl;

}


  return std::vector<libbf::download>();
}
