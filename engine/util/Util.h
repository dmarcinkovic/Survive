//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_UTIL_H
#define SURVIVE_UTIL_H

#include <vector>
#include <string>
#include <regex>
#include "../text/Character.h"

class Util
{
private:
    static int getNumber(const std::string& string);

public:
    static std::vector<std::string> split(const std::string &string, const std::string &delimiter);

    static Character getCharacter(const std::vector<std::string> &line);
};


#endif //SURVIVE_UTIL_H
