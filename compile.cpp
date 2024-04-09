#include <iostream>
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

int main() {
    std::string fileName = "1.txt"; // Укажите имя файла здесь
    createProgram(fileName);
    return 0;
}
