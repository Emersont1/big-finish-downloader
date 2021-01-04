#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::do_get_images(std::future<void> should_close) {
  while (should_close.wait_for(std::chrono::seconds(0)) !=
         std::future_status::ready) {
    if (!get_images.empty()) {
      auto        x = get_images.front();
      std::string y = std::to_string(x.download_number);
      if (!std::filesystem::exists(cache + "img/" + y + ".jpg")) {
        std::ofstream of(cache + "img/" + y + ".jpg", std::ios::binary);
        cpr::Response r = cpr::Get(cpr::Url{
            "https://www.bigfinish.com/image/release/" + y + "/small.jpg"});
        of.write(r.text.c_str(), r.text.size());
        of.close();
      }
      auto pixbuf = gdk_pixbuf_new_from_file_at_size(
          (cache + "img/" + y + ".jpg").c_str(), 50, 50, nullptr);
      get_images.pop();
      got_images.emplace(x, pixbuf);
    }
  }
}