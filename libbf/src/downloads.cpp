#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <vector>

#include <cpr/cpr.h>

#include <libbf/downloads.hpp>

void libbf::download::download_mp3(libbf::login_cookie & cookie,
                                   std::filesystem::path output_directory) {
  const cpr::WriteCallback cb([&](std::string header) -> bool { return true; });
  std::ofstream            of(output_directory /
                       (std::to_string(download_number) + ".zip"),
                   std::ios::binary);
  cpr::Response            r =
      cpr::Get(cpr::Url{"https://www.bigfinish.com/releases/download/" +
                        std::to_string(download_number) + "/audiobook"},
               cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                            {"CAKEPHP", cookie.get_cakephp()}},
               cb);
}