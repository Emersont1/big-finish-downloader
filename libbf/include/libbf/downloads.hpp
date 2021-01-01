#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <libbf/login_cookie.hpp>

namespace libbf {
class download {
  std::string      name;
  std::uint32_t    download_number;
  bool             m4b_availible;
  std::vector<int> supplementary_media;

public:
  download(std::string name, std::uint32_t download_number, bool m4b_availible,
           std::vector<int> supplementary_media)
      : name(name), download_number(download_number),
        m4b_availible(m4b_availible), supplementary_media(supplementary_media) {
  }

  void download_mp3(
      std::filesystem::path output_directory = std::filesystem::path());

  static std::vector<download> get_downloads(login_cookie & cookie);
};

} // namespace libbf
