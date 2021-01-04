#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

int libbf::gui::main_window::download(int value) {

  for (int i = 0; i < 100; i++) {
    download_progress = i / 100.0;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return value;
}