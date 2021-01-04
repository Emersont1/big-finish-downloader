#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

int libbf::gui::main_window::download(libbf::download value) {
  for (int i = 0; i < 50; i++) {
    download_progress = i / 50.0;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    status_ii = std::to_string(download_progress*100);
  }
  return value.download_number;
}