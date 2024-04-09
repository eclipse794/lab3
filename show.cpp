#include <iostream>
#include <cstdlib> // для функции system()

int main() {
    // Выполняем команду attrib для удаления атрибута "скрытый" у всех файлов
    system("attrib -h *.*");

    std::cout << "Удалены атрибуты \"скрытый\" у всех файлов в текущей директории" << std::endl;

    return 0;
}
