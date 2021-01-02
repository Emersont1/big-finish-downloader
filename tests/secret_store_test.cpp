#include <libbf/gui/secret_storage.hpp>

// relies on exports from big-finish-downloader-gtk as its currently not in its own library
// TODO: make a drop-in cross platform secret storage library libbf-secrets

int main(int argc, char ** argv) {
  libbf::login_cookie l = libbf::login_cookie::example();
  libbf::gui::store(l);

  std::cout << libbf::gui::retrieve() << std::endl;
  return 0;
}