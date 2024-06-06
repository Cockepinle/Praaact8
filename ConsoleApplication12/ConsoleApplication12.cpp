#include <iostream>
#include <Windows.h>
#include <string>
#include "Header.h"
__declspec(dllexport) bool contains_chars(const char* str, const char* chars) {
    std::string s(str);
    std::string c(chars);

    for (char ch : c) {
        if (s.find(ch) == std::string::npos) {
            return false;
        }
    }
    return true;
}