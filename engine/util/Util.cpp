//
// Created by david on 29. 03. 2020..
//

#include <iostream>
#include "Util.h"

std::vector<std::string> Util::split(const std::string &string, const std::string &delimiter)
{
    std::regex pattern(delimiter);
    std::sregex_token_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_token_iterator end;

    std::vector<std::string> result;
    std::copy(begin, end, std::back_inserter(result));

    return result;
}

int Util::getNumber(const std::string &string)
{
    int index = string.find('=');
    return std::stoi(string.substr(index + 1));
}

Character Util::getCharacter(const std::vector<std::string> &line)
{
    int id = getNumber(line[1]);
    int x = getNumber(line[2]);
    int y = getNumber(line[3]);
    int width = getNumber(line[4]);
    int height = getNumber(line[5]);
    int xOffset = getNumber(line[6]);
    int yOffset = getNumber(line[7]);
    int advance = getNumber(line[8]);

    return Character(id, x, y, width, height, xOffset, yOffset,advance);
}
