#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createProgram(const char* fileName) {
    // Код программы на C, который мы хотим создать
    const char* programCode = 
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "#include <string.h>\n"
    "\n"
    "int main() {\n"
    "    // Путь к вашему .txt файлу\n"
    "    const char* txtFilePath = \"";

    // Открываем файл для записи
    FILE* outputFile = fopen("temp.c", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Не удалось создать временный файл для записи!\n");
        return;
    }

    // Записываем начало программы
    fputs(programCode, outputFile);
    // Записываем путь к файлу
    fputs(fileName, outputFile);
    // Завершаем запись программы
    fputs("\";\n"
    "\n"
    "    // Формируем команду для открытия файла в ассоциированной программе\n"
    "    char command[100];\n"
    "    sprintf(command, \"notepad.exe %s\", txtFilePath);\n"
    "\n"
    "    // Выполняем команду с помощью системного вызова\n"
    "    system(command);\n"
    "\n"
    "    return 0;\n"
    "}\n", outputFile);

    // Закрываем файл
    fclose(outputFile);

    // Компилируем временный файл с помощью gcc
    int compileResult = system("gcc -o temp.exe temp.c");

    // Удаляем временный файл
    remove("temp.c");

    if (compileResult != 0) {
        fprintf(stderr, "Ошибка при компиляции программы!\n");
        return;
    }

    printf("Новая программа успешно создана и скомпилирована в temp.exe\n");
}

int main() {
    const char* fileName = "2.txt"; // Укажите имя файла здесь
    createProgram(fileName);
    return 0;
}
