#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

std::vector<std::pair<libbf::download, GdkPixbuf*>> libbf::gui::main_window::get_items(
        libbf::login_cookie c) {
    auto ds = libbf::download::get_downloads(c);
    std::vector<std::pair<libbf::download, GdkPixbuf*>> m;
    for (auto x : ds) {
        std::string y = std::to_string(x.image_number);
        if (!std::filesystem::exists(cache /( "img/" + y + ".jpg"))) {
            std::ofstream of(cache / ("img/" + y + ".jpg"), std::ios::binary);
            cpr::Response r = cpr::Get(
                    cpr::Url{"https://www.bigfinish.com/image/release/" + y + "/small.jpg"});
            of.write(r.text.c_str(), r.text.size());
            of.close();
        }
        auto pixbuf = gdk_pixbuf_new_from_file_at_size((cache /( "img/" + y + ".jpg")).string().c_str(), 48,
                                                       48, nullptr);
        m.push_back(std::make_pair(x, pixbuf));
    }
    return m;
}