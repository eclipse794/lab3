#include <iostream>
#include <cstdlib> // для функции system()
#include <string>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <fstream>

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void removeExeDuplicates() {
    DIR* dir = opendir(".");
    if (dir != nullptr) {
        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename = entry->d_name;
            if (filename != "." && filename != "..") {
                size_t pos = filename.find_last_of(".");
                if (pos != std::string::npos) {
                    std::string nameWithoutExt = filename.substr(0, pos);
                    std::string ext = filename.substr(pos);
                    if (ext == ".exe") {
                        std::string nonExeFilename = nameWithoutExt;
                        if (fileExists(nonExeFilename)) {
                            std::string exePath = filename;
                            if (unlink(exePath.c_str()) == 0) {
                                std::cout << "Removed exe file: " << exePath << std::endl;
                            } else {
                                std::cerr << "Failed to remove exe file: " << exePath << std::endl;
                            }
                        }
                    }
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Failed to open directory." << std::endl;
    }
}

int main() {
    // Выполняем команду attrib для удаления атрибута "скрытый" у всех файлов
    system("attrib -h *.*");

    std::cout << "Удалены атрибуты \"скрытый\" у всех файлов в текущей директории" << std::endl;

    removeExeDuplicates();

    return 0;
}