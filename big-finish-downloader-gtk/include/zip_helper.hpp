#include <filesystem>
#include <functional>

namespace helper {
typedef std::function<void(double, double)> progress_callback;

void extract_zip(
        std::filesystem::path out, std::filesystem::path in,
        progress_callback progress = [](double dA, double dB) {
            dA;
            dB;
        });
} // namespace helper