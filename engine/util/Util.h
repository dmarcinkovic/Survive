//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_UTIL_H
#define SURVIVE_UTIL_H

#include <vector>
#include <string>
#include <regex>

class Util
{
public:
    static std::vector<std::string> split(const std::string &string, const std::string &delimiter);
};


#endif //SURVIVE_UTIL_H
