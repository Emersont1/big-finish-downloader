#include <libbf/gui/modules/main_window.hpp>

#include <iostream>

int libbf::gui::main_window::update_func(void * d) {
  auto m = (libbf::gui::main_window *) d;

  if (!m->dl.active()) {
    auto f = [](libbf::login_cookie cookie) -> libbf::downloads_t {
      return libbf::download::get_downloads(cookie);
    };
    std::function<libbf::downloads_t()> i = std::bind(f, m->cookie);
    m->dl.begin(i);
  }

  if (m->dl.complete_trigger()) {
    for (auto x = m->dl->begin(); x != m->dl->end(); x++) {
      GtkTreeIter a;
      m->get_images.push(*x);
    }
  }

  m->dl.update();

  if (!m->got_images.empty()) {
    auto x = m->got_images.front();
    bool e = std::filesystem::exists(
        m->cache + std::to_string(x.first.download_number) + ".lock");
    gtk_list_store_insert_with_values(m->list_downloading, nullptr, -1, 0,
                                      x.first.name.c_str(), 1, !e, 2, x.second,
                                      3, x.first.download_number, -1);
    m->got_images.pop();
  }
  return 1;
}