//
// Created by diguie_t on 11/19/2017.
//

#include <vector>
#include "windows.h"
#include "include/internal/cef_string.h"
#include "Utils.hh"

std::string Utils::getApplicationDir() {
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR   wpath[MAX_PATH];

    GetModuleFileNameW(hModule, wpath, MAX_PATH);
    std::wstring wide(wpath);

    std::string path = CefString(wide);
    path = path.substr( 0, path.find_last_of("\\/") );
    return (path);
}

std::vector<std::string> Utils::split(const std::string &str, const std::string &sep) {
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current = std::strtok(cstr,sep.c_str());
    while (current != nullptr){
        arr.emplace_back(current);
        current = std::strtok(nullptr,sep.c_str());
    }
    return (arr);
}

std::u16string Utils::to16string(const std::string &str) {
    return (std::u16string(str.begin(), str.end()));
}

std::u16string Utils::to16string(const std::wstring &str) {
    return (std::u16string(str.begin(), str.end()));
}

std::wstring Utils::toWstring(const std::u16string &str) {
    return (std::wstring(str.begin(), str.end()));
}

std::string Utils::toString(const std::wstring &str) {
    return (std::string(str.begin(), str.end()));
}

const std::u16string &Utils::escapeChar(std::u16string &str, const std::vector<char> &toEscape, char16_t eschapeChar) {
    bool needEscapeChar = false;
    for (char16_t c : str) {
        for (char escape : toEscape) {
            const char16_t convertedChar = static_cast<char16_t>(escape);
            if (c == convertedChar) {
                needEscapeChar = true;
            }
        }
    }

    if (needEscapeChar) {
        str = eschapeChar + str;
    }

    return (str);
}

std::wstring Utils::toWstring(const std::string &str) {
    return (std::wstring(str.begin(), str.end()));
}
