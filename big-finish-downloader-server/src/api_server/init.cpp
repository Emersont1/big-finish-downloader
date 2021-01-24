#include <libbf/server/api_server.hpp>

libbf::server::api_server::api_server() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8000));

    httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
}

void libbf::server::api_server::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setup_route();
}

void libbf::server::api_server::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void libbf::server::api_server::setup_route() {
    Pistache::Rest::Routes::Post(
            router, "/add_login",
            Pistache::Rest::Routes::bind(&libbf::server::api_server::add_login, this));
    Pistache::Rest::Routes::Get(
            router, "/get_queue",
            Pistache::Rest::Routes::bind(&libbf::server::api_server::get_queue, this));
    Pistache::Rest::Routes::Get(
            router, "/refresh_queue",
            Pistache::Rest::Routes::bind(&libbf::server::api_server::refresh_queue, this));
    Pistache::Rest::Routes::Get(
            router, "/get_status",
            Pistache::Rest::Routes::bind(&libbf::server::api_server::get_status, this));
}

void libbf::server::api_server::refresh_queue(const Pistache::Http::Request& req,
                                              Pistache::Http::ResponseWriter response) {
    internal_server.refresh_downloads();
    write_error(response, Pistache::Http::Code::Ok, "Refreshed Queue");
}