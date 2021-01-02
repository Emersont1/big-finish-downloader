#include <libbf/gui/modules/main_window.hpp>

int main(int argc, char ** argv) {
  gtk_init(&argc, &argv);
  libbf::gui::main_window x;
  gtk_main();
}