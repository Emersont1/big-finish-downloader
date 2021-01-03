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
      gtk_list_store_insert_with_values(m->list_downloading, nullptr, -1, 0,
                                        x->name.c_str(), 1, false, 2, nullptr,
                                        -1);
    }
  }

  m->dl.update();
  return 1;
}