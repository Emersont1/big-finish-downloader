#include <fstream>

#include <zip_helper.hpp>

#include <libzippp/libzippp.h>

#include <spdlog/spdlog.h>

void helper::extract_zip(std::filesystem::path out, std::filesystem::path in,
                         helper::progress_callback progress) {
    spdlog::info("Extracting Archive {} to {}", in.string(), out.string());
    libzippp::ZipArchive zf(in.string());
    zf.open(libzippp::ZipArchive::ReadOnly);

    std::vector<libzippp::ZipEntry> entries = zf.getEntries();
    spdlog::info("Zip has {} entries", entries.size());
    int i = 0;
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        progress(i, entries.size());

        std::filesystem::path o_path = out / std::filesystem::path(it->getName()).filename();
        spdlog::info ("file {}", o_path.string());
        std::filesystem::create_directories(o_path.parent_path());
        std::ofstream output(o_path);
        it->readContent(output);
        output.close();
        i++;
    }

    zf.close();
    spdlog::info("Done Extracting");
}