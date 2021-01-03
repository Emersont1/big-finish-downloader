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
    std::cout << "completed ... updating obects!" << std::endl;
  }

  m->dl.update();
  return 1;
}