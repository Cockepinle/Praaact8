#include <iostream>
#include <windows.h>
#include <string>

extern "C" __declspec(dllexport) bool contains_chars(const char* input, const char* chars) {
    std::string inputString(input);
    std::string charsToFind(chars);

    for (char c : charsToFind) {
        if (inputString.find(c) == std::string::npos) {
            return false;
        }
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "RUssian");

    std::string inputString;
    std::string charsToFind;

    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);

    std::cout << "Введите символы для поиска: ";
    std::getline(std::cin, charsToFind);

    HINSTANCE load;
    load = LoadLibrary(L"ConsoleApplication12.dll");

    typedef bool (*contains_chars_func)(const char*, const char*);
    contains_chars_func containsChars = (contains_chars_func)GetProcAddress(load, "contains_chars");
    if (!containsChars) {
        std::cerr << "Не удалось получить адрес функции." << std::endl;
        FreeLibrary(load);
        return 1;
    }

    bool result = containsChars(inputString.c_str(), charsToFind.c_str());
    std::cout << (result ? "Все символы найдены в строке." : "Не все символы найдены в строке.") << std::endl;

    FreeLibrary(load);

    return 0;
}