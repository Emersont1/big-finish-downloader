#include <iostream>
#include <libbf/downloads.hpp>
#include <libbf/login_cookie.hpp>

int main(int argc, char ** argv) {
  std::cout << "Enter Email" << std::endl;
  std::string email;
  std::cin >> email;

  std::cout << "Enter password" << std::endl;
  std::string password;
  std::cin >> password;
  libbf::login_cookie l = libbf::login_cookie::login(email, password);

  auto ds = libbf::download::get_downloads(l);

  ds[0].download_mp3(l);
  return 0;
}
