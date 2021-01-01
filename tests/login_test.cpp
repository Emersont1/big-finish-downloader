#include <iostream>
#include <libbf/login_cookie.hpp>

int main(int argc, char ** argv) {
  std::cout << "Enter Email" << std::endl;
  std::string email;
  std::cin >> email;

  std::cout << "Enter password" << std::endl;
  std::string password;
  std::cin >> password;
  libbf::login_cookie l = libbf::login_cookie::login(email, password);

  std::cout << l << std::endl;
  return 0;
}
