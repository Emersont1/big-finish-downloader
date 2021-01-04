#include <libbf/gui/modules/main_window.hpp>

#include <iostream>

int libbf::gui::main_window::update_func(void * d) {
  auto m = (libbf::gui::main_window *) d;

  gtk_progress_bar_set_fraction((GtkProgressBar *) m->progress_bar,
                                m->download_progress);

  if (!m->items_fut.valid()) 
    m->items_fut = std::async(std::launch::async,&libbf::gui::main_window::get_items, m, m->cookie);

  if (m->items_fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    m->items = m->items_fut.get();
    for (auto x=  m->items.begin(); x !=  m->items.end(); ++x) {
      m->add_to_view(*x);
    }
  }

  if (!m->downloader.active() || m->downloader.complete_trigger()) {
    if (m->downloader.complete_trigger()) {
      std::cout << *(m->downloader) << std::endl;
    }
    auto i = std::bind(&libbf::gui::main_window::download, m, 1);
    m->downloader.begin(i);
  }

  //m->items_scrape.update();
  m->downloader.update();


  return 1;
}