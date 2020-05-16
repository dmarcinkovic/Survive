//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_UTIL_H
#define SURVIVE_UTIL_H

#include <vector>
#include <string>
#include <regex>
#include <optional>

#include "../text/Character.h"

class Util
{
private:
    static Character getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH);

    static void removeTrailingSpaces(std::string &string);

public:
    static float getNumber(const std::string &string, char delimiter = '=');

    static std::vector<std::string> splitByRegex(const std::string &string);

    static Character getCharacterFromFntFile(const std::vector<std::string> &line, float w, float h);

    static std::optional<Character> getCharacterFromJsonFile(const std::string &line, float scaleW, float scaleH);

    static std::vector<std::string> split(std::string string, char delimiter);
};


#endif //SURVIVE_UTIL_H
