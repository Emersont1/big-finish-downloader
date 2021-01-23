#include <iostream>
#include <string>

#include <libbf/exceptions.hpp>
#include <libbf/server/api_server.hpp>
#include <nlohmann/json.hpp>

void libbf::server::api_server::add_login(const Pistache::Http::Request& req,
                                          Pistache::Http::ResponseWriter response) {
    nlohmann::json request;
    std::string email, password;

    // will throw an exception if there is no key in the json (or if it is invalid format)
    try {
        request = nlohmann::json::parse(req.body());
        email = request["email"].get<std::string>();
        password = request["password"].get<std::string>();
    } catch (nlohmann::json::exception e) {
        std::string s(e.what());
        write_error(response, Pistache::Http::Code::Bad_Request, s);
        return;
    }

    try {
        auto l = libbf::login_cookie::login(email, password);
        internal_server.add_login(l);
        write_error(response, Pistache::Http::Code::Ok, "Login Successful");
    } catch (libbf::login_failed_exception e) {
        write_error(response, Pistache::Http::Code::Bad_Request,
                    "Login with email \"" + email + "\" and password failed");
    }
    return;
}