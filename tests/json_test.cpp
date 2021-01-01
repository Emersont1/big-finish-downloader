#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

int main(int argc, char ** argv) {
  std::string _json = "{\"hello\":\"there\"}";

  nlohmann::json j = nlohmann::json::parse(_json);

  std::cout << j["hello"].get<std::string>() << std::endl;

  return 0;
}
