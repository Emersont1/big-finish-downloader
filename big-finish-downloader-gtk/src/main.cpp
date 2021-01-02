#include <libbf/gui/modules/login.hpp>

int main(int argc, char ** argv) {
  gtk_init(&argc, &argv);
  libbf::gui::login x;
  gtk_main();
}