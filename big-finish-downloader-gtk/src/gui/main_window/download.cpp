#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

#include <cpr/cpr.h>

#include <libbf/gui/modules/main_window.hpp>

int libbf::gui::main_window::download(libbf::download value, std::shared_future<void> v) {
    value.download_mp3(
            cookie, dest_dir,
            [&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal, size_t uploadNow) {
                download_progress.store(
                        (double) downloadNow / (downloadTotal+1));
                if (v.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {
                    return true;

                } else {
                    return false;
                }

                return true;
            });

    return value.image_number;
}