#include <iostream>
#include <libbf/downloads.hpp>
#include <libbf/login_cookie.hpp>

#include <nlohmann/json.hpp>

int main(int argc, char** argv) {
    std::cout << "Enter Email" << std::endl;
    std::string email;
    std::cin >> email;

    std::cout << "Enter password" << std::endl;
    std::string password;
    std::cin >> password;
    libbf::login_cookie l = libbf::login_cookie::login(email, password);

    auto ds = libbf::download::get_downloads(l);
    nlohmann::json j = ds;
    std::cout << j.dump(2) << std::endl;

    return 0;
}
