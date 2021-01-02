#include <ui/login.hpp>

int main(int argc, char ** argv) {
  gtk_init(&argc, &argv);
  ui::login x;
  x.show();
  gtk_main();
}