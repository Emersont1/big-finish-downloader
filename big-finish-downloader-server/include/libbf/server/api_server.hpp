#pragma once
#include <memory>

#include <libbf/server/server.hpp>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

namespace libbf::server {
class api_server {
  public:
    explicit api_server();
    void init(size_t thr = 2);
    void start();

  private:
    void setup_route();
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
    server internal_server;

    // Endpoints
    void add_login(const Pistache::Http::Request& req, Pistache::Http::ResponseWriter response);
    void refresh_queue(const Pistache::Http::Request& req, Pistache::Http::ResponseWriter response);
    void get_queue(const Pistache::Http::Request& req, Pistache::Http::ResponseWriter response);
    void get_status(const Pistache::Http::Request& req, Pistache::Http::ResponseWriter response);

    static void write_error(Pistache::Http::ResponseWriter& response, Pistache::Http::Code e,
                            std::string errormsg = "");
};
} // namespace libbf::server
