#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <vector>

#include <cpr/cpr.h>

#include <libbf/downloads.hpp>

void libbf::download::download_mp3(
        libbf::login_cookie& cookie, std::filesystem::path output_directory,
        std::function<bool(size_t, size_t, size_t, size_t)> progress_callback) {
    std::ofstream of(output_directory / (name + ".zip"),
                     std::ios::binary);

    const cpr::WriteCallback cb([&](std::string data) -> bool {
         of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com/releases/download/" +
                                        std::to_string(download_number)},
                               cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                                            {"CAKEPHP", cookie.get_cakephp()}},
                               cb,cpr::ProgressCallback{progress_callback});
   

    std::cout << r.status_code << std::endl;
}