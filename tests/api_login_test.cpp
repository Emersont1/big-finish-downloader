#include <iostream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

int main(int argc, char** argv) {
    std::cout << "Enter Email" << std::endl;
    std::string email;
    std::cin >> email;

    std::cout << "Enter password" << std::endl;
    std::string password;
    std::cin >> password;


    cpr::Response r = cpr::Post(cpr::Url{"https://www.bigfinish.com/apiv3/login.json"},
                                cpr::Payload{
                                        {"data[Customer][email_address]", email},
                                        {"data[Customer][password]", password},
                                });

    nlohmann::json j = nlohmann::json::parse(r.text);
    std::cout << j << std::endl;

    if (j.contains("login_failed") && j["login_failed"].get<bool>()) {
        std::cout << "failed" << std::endl;
        return 1;
    }

    std::string token = j["Customer"]["token"].get<std::string>();
    cpr::Response releases = cpr::Get(cpr::Url{"https://www.bigfinish.com/apiv3/releases.json"},
                                      cpr::Parameters{
                                              {"token", token},
                                      });
    std::cout << releases.text << std::endl;
    return 0;
}
