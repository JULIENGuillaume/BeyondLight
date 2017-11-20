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
};


#endif //CEFOFFSCREEN_UTILS_HH
