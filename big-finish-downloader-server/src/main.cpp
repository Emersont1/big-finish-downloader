#include <iostream>

#include <libbf/server/server.hpp>

int main() {

    libbf::server::server download_server;
    std::cout << "Enter Email" << std::endl;
    std::string email;
    std::cin >> email;

    std::cout << "Enter password" << std::endl;
    std::string password;
    std::cin >> password;
    libbf::login_cookie l = libbf::login_cookie::login(email, password);

    std::cout << l << std::endl;
    download_server.add_login(l);
    download_server.refresh_downloads();
    while (true);
    
    return 0;
}