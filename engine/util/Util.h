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
    static Character getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH);

public:
    static float getNumber(const std::string &string);

    static std::vector<std::string> split(const std::string &string, const std::string &delimiter);

    static Character getCharacterFromFntFile(const std::vector<std::string> &line, float w, float h);

    static Character getCharacterFromJsonFile(const std::string &line, float scaleW, float scaleH);
};


#endif //SURVIVE_UTIL_H
