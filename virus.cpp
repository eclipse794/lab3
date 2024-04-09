#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
void createProgram(const std::string& fileName) {
    // Код программы на C++, который мы хотим создать
    std::string programCode = R"(
#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    // Путь к вашему .txt файлу
    std::string txtFilePath = ")" + fileName + R"(";

    // Формируем команду для открытия файла в ассоциированной программе
    std::string command = "notepad.exe " + txtFilePath;

    // Выполняем команду с помощью системного вызова, игнорируя возвращаемое значение
    system(command.c_str());

    return 0;
}
    )";

    // Создаем временный файл для записи исходного кода
    std::ostringstream tempFileNameStream;
    tempFileNameStream << "temp_" << std::rand() << ".cpp";
    std::string tempFileName = tempFileNameStream.str();

    std::ofstream outputFile(tempFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось создать временный файл для записи!" << std::endl;
        return;
    }

    // Записываем код программы в файл
    outputFile << programCode;
    outputFile.close();

    // Компилируем временный файл с помощью g++
    std::string compileCommand = "g++ -o " + fileName+ ".exe " + tempFileName;
    int compileResult = std::system(compileCommand.c_str());

    // Удаляем временный файл
    std::remove(tempFileName.c_str());

    if (compileResult != 0) {
        std::cerr << "Ошибка при компиляции программы!" << std::endl;
        return;
    }

    std::cout << "Новая программа успешно создана и скомпилирована в " << fileName.substr(0, fileName.find_last_of('.')) + ".exe" << std::endl;
}
bool ends_with(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main() {
    DIR *dir;
    struct dirent *ent;
    struct stat fileStat;
    std::vector<std::string> txtFiles; // Массив для хранения названий txt-файлов

    if ((dir = opendir(".")) != nullptr) {
        std::cout << "Txt files in current directory:" << std::endl;
        while ((ent = readdir(dir)) != nullptr) {
            stat(ent->d_name, &fileStat);
            if (S_ISREG(fileStat.st_mode) && ends_with(ent->d_name, ".txt")) {
                std::cout << ent->d_name << std::endl;
                txtFiles.push_back(ent->d_name); // Добавляем название txt-файла в массив
                system(("attrib +h " + std::string(ent->d_name)).c_str()); // скрываем текущий файл // Добавляем название txt-файла в массив
            }
        }
        closedir(dir);

        // Выводим содержимое массива названий txt-файлов
        std::cout << "Txt filenames stored in array:" << std::endl;
        for (const auto& filename : txtFiles) {
            std::cout << filename << std::endl;
            createProgram(filename);

        }

        std::cout << "Press Enter to exit...";
        std::cin.get(); // Ждем нажатия клавиши Enter

    } else {
        std::cerr << "Error opening directory" << std::endl;
        return 1;
    }

    return 0;
}
