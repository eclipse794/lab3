#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    // Путь к вашему .txt файлу
    std::string txtFilePath = "1.txt";

    // Формируем команду для открытия файла в ассоциированной программе
    std::string command = "notepad.exe " + txtFilePath;

    // Выполняем команду с помощью системного вызова, игнорируя возвращаемое значение
    system(command.c_str());

    return 0;
}
