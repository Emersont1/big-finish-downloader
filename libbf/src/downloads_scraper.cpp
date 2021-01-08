#include <iostream>

#include <cpr/cpr.h>

#include <libbf/downloads.hpp>
#include <libbf/exceptions.hpp>

void libbf::from_json(const nlohmann::json& j, download& p) {
    j.at("Release").at("name").get_to(p.name);
    p.image_number = std::stoi(j.at("Release").at("id").get<std::string>());
    p.download_number = std::stoi(j.at("ReleaseDownload").at("id").get<std::string>());
}

void libbf::to_json(nlohmann::json& j, const download& r) {
    j = nlohmann::json{{"name", r.name},
                       {"download_number", r.download_number},
                       {"image_number", r.image_number},
                       {"m4b_available", r.m4b_available},
                       {"supplementary_media", r.supplementary_media}};
}


std::vector<libbf::download> libbf::download::get_downloads(libbf::login_cookie& cookie) {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com/apiv3/releases.json"},
                               cpr::Parameters{{"token", cookie.get_token()}});
    nlohmann::json j = nlohmann::json::parse(r.text);
    return j;
}