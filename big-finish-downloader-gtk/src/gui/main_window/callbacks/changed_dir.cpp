#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::changed_dir() {
  dest_dir = std::string(g_settings_get_string(settings, "download-directory"));
  if (dest_dir[0] == '~') {
    dest_dir = std::getenv("HOME") + dest_dir.substr(1);
  }
  load_downloaded();
}
