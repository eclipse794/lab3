#include <iostream>
#include <cstdlib> // для функции system()

int main() {
    // Выполняем команду attrib для установки атрибута "скрытый" для всех файлов
    system("attrib +h *.*");

    std::cout << "Скрыты все файлы в текущей директории" << std::endl;

    return 0;
}
