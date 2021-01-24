#include <functional>
#include <iostream>
#include <string>

#include <libbf/exceptions.hpp>
#include <libbf/server/api_server.hpp>
#include <nlohmann/json.hpp>

void libbf::server::api_server::get_status(const Pistache::Http::Request& req,
                                           Pistache::Http::ResponseWriter response) {
    auto status = internal_server.get_status();

    nlohmann::json j;
    j["progress"] = std::get<0>(status);
    j["status_i"] = std::get<1>(status);
    j["status_ii"] = std::get<2>(status);
    j["image"] = std::get<3>(status);

    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    auto stream = response.stream(Pistache::Http::Code::Ok);
    std::string x = j.dump();
    stream << x.c_str() << Pistache::Http::ends;
    return;
}