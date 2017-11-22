//
// Created by diguie_t on 11/19/2017.
//

#ifndef CEFOFFSCREEN_UTILS_HH
#define CEFOFFSCREEN_UTILS_HH

#include <string>

class Utils {
public:
    static std::string getApplicationDir();
    static std::vector<std::string> split(const std::string &str, const std::string &separator);
    static std::u16string to16string(const std::string &str);
    static std::u16string to16string(const std::wstring &str);
    static std::wstring toWstring(const std::u16string &str);
    static std::wstring toWstring(const std::string &str);
    static std::string toString(const std::wstring &str);
    static const std::u16string &escapeChar(std::u16string &str, const std::vector<char> &toEscape, char16_t eschapeChar);
};


#endif //CEFOFFSCREEN_UTILS_HH
