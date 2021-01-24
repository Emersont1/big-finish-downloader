#include <libbf/server/api_server.hpp>
#include <nlohmann/json.hpp>

void libbf::server::api_server::write_error(Pistache::Http::ResponseWriter& response,
                                            Pistache::Http::Code e, std::string errormsg) {
    std::string error_string;
    switch (e) {
        case Pistache::Http::Code::Bad_Request:
            error_string = "Invalid JSON request";
            break;
        case Pistache::Http::Code::Internal_Server_Error:
            error_string = "Internal Server Error";
            break;
        case Pistache::Http::Code::Not_Implemented:
            error_string = "Not Implemented";
            break;
        case Pistache::Http::Code::Ok:
            error_string = "Ok";
            break;
        default:
            error_string = "Unknown Error";
            break;
    }

    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));

    auto stream = response.stream(e);

    nlohmann::json j = {
            {"ERROR", error_string},
            {"number", (int) e},
            {"message", errormsg},
    };
    std::string dumped_json = j.dump() + "\n";
    stream << dumped_json.c_str() << Pistache::Http::ends;
}