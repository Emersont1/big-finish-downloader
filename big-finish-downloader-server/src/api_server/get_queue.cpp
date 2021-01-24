#include <functional>
#include <iostream>
#include <string>

#include <libbf/exceptions.hpp>
#include <libbf/server/api_server.hpp>
#include <nlohmann/json.hpp>

void libbf::server::api_server::get_queue(const Pistache::Http::Request& req,
                                          Pistache::Http::ResponseWriter response) {
    std::vector<std::pair<libbf::download, std::string>> data;

    auto queue = internal_server.get_queue();

    auto func = [](std::pair<libbf::download, std::shared_ptr<libbf::login_cookie>> a)
            -> std::pair<libbf::download, std::string> {
        return std::make_pair(a.first, a.second->get_email());
    };

    std::transform(queue.begin(), queue.end(), std::back_inserter(data), func);

    nlohmann::json j = data;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    auto stream = response.stream(Pistache::Http::Code::Ok);
    std::string x = j.dump();
    stream << x.c_str() << Pistache::Http::ends;
    return;
}