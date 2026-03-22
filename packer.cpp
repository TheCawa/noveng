#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void processFile(const fs::path& path, const std::string& key) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return;

    std::vector<char> buffer((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    for (size_t i = 0; i < buffer.size(); ++i) {
        buffer[i] ^= key[i % key.length()];
    }

    std::ofstream out(path, std::ios::binary);
    out.write(buffer.data(), buffer.size());
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    std::string targetDir = argv[1];
    std::string key = argv[2];

    for (auto& p : fs::recursive_directory_iterator(targetDir)) {
        if (p.is_regular_file()) {
            if (p.path().extension() != ".log" && p.path().extension() != ".json") {
                processFile(p.path(), key);
            }
        }
    }
    return 0;
}