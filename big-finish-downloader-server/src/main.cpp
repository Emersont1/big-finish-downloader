#include <iostream>

#include <libbf/server/api_server.hpp>

int main() {
    libbf::server::api_server download_server;
    download_server.init(1);
    download_server.start();
    return 0;
}