#include <libbf/gui/modules/main_window.hpp>

#include <iostream>

int libbf::gui::main_window::update_func(void * d) {
  auto m = (libbf::gui::main_window *) d;

  gtk_progress_bar_set_fraction((GtkProgressBar *) m->progress_bar,
                                m->download_progress);

  if (!m->items_scrape.active()) {
    auto i = std::bind(libbf::download::get_downloads, m->cookie);
    m->items_scrape.begin(i);
  }

  if (m->items_scrape.complete_trigger()) {
    for (auto x = m->items_scrape->begin(); x != m->items_scrape->end(); x++) {
      m->get_images.push(*x);
    }
  }

  if (!m->downloader.active() || m->downloader.complete_trigger()) {
    if (m->downloader.complete_trigger()) {
      std::cout << *(m->downloader) << std::endl;
      //m->downloaded_ids.push_back();
    }
    auto i = std::bind(&libbf::gui::main_window::download, m, 1);
    m->downloader.begin(i);
  }

  //m->items_scrape.update();
  m->downloader.update();

  while (!m->got_images.empty()) {
    auto x = m->got_images.front();
    m->add_to_view(x);
    m->items[x.first.download_number] = x;
    m->got_images.pop();
  }
  return 1;
}