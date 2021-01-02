#include <libbf/gui/secret_storage.hpp>

int main(int argc, char ** argv) {
  libbf::login_cookie l = libbf::login_cookie::example();
  libbf::gui::store(l);
  return 0;
}