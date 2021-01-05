#include <fstream>

#include <zip_helper.hpp>

#include <libzippp/libzippp.h>


void helper::extract_zip(std::filesystem::path out, std::filesystem::path in,
                         helper::progress_callback progress) {
    libzippp::ZipArchive zf(in);
    zf.open(libzippp::ZipArchive::ReadOnly);

    std::vector<libzippp::ZipEntry> entries = zf.getEntries();
    int i = 0;
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        progress(i, entries.size());

        std::filesystem::path o_path = out / it->getName();
        std::filesystem::create_directories(o_path.parent_path());
        std::ofstream output(o_path);
        it->readContent(output);
        output.close();
        i++;
    }

    zf.close();
}