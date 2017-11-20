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