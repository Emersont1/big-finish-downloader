#include <iostream>
#include <libbf/downloads.hpp>
#include <libbf/login_cookie.hpp>

#include <nlohmann/json.hpp>
namespace libbf {
void to_json(nlohmann::json& j, const download& r) {
    j = nlohmann::json{{"name", r.name},
                       {"download_number", r.download_number},
                       {"m4b_available", r.m4b_available},
                       {"supplementary_media", r.supplementary_media}};
}
} // namespace libbf
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
