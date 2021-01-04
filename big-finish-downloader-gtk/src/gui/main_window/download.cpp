#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

int libbf::gui::main_window::download(libbf::download value, std::future<void> v) {
    for (int i = 0; i < 100; i++) {
        if (v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {
            download_progress = i / 99.0;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            status_ii = std::to_string(download_progress * 100);
        }
    }
    return value.download_number;
}