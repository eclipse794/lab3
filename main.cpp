#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

int main() {
    DIR *dir;
    struct dirent *ent;
    struct stat fileStat;

    if ((dir = opendir(".")) != nullptr) {
        std::cout << "Files in current directory:" << std::endl;
        while ((ent = readdir(dir)) != nullptr) {
            stat(ent->d_name, &fileStat);
            if (S_ISREG(fileStat.st_mode)) {
                std::cout << ent->d_name << std::endl;

                // Проверяем расширение файла
                std::string filename = ent->d_name;
                if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt") {
                    // Открываем исходный файл для чтения
                    std::ifstream sourceFile(filename);
                    if (sourceFile.is_open()) {
                        // Создаем имя для копии файла с расширением .exe
                        std::string exeFilename = filename.substr(0, filename.size() - 4) + ".exe";
                        // Открываем новый файл для записи
                        std::ofstream destFile(exeFilename, std::ios::binary);
                        if (destFile.is_open()) {
                            // Копируем содержимое исходного файла в новый файл
                            destFile << sourceFile.rdbuf();
                            destFile.close();
                            std::cout << "Created " << exeFilename << std::endl;
                        } else {
                            std::cerr << "Error creating file: " << exeFilename << std::endl;
                        }
                        sourceFile.close();
                    } else {
                        std::cerr << "Error opening file: " << filename << std::endl;
                    }
                }
            }
        }
        closedir(dir);

        std::cout << "Press Enter to exit...";
        std::cin.get(); // Ждем нажатия клавиши Enter

    } else {
        std::cerr << "Error opening directory" << std::endl;
        return 1;
    }

    return 0;
}
