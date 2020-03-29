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
    std::copy(std::make_move_iterator(begin), std::make_move_iterator(end), std::back_inserter(result));

    return result;
}

float Util::getNumber(const std::string &string)
{
    int index = string.find('=');
    return std::stof(string.substr(index + 1));
}

Character Util::getCharacter(const std::vector<std::string> &line, float w, float h)
{
    float id = getNumber(line[1]);
    float x = getNumber(line[2]);
    float y = getNumber(line[3]);
    float width = getNumber(line[4]);
    float height = getNumber(line[5]);
    float xOffset = getNumber(line[6]);
    float yOffset = getNumber(line[7]);
    float advance = getNumber(line[8]);

    return Character(id, x, y, width, height, xOffset, yOffset, advance, w, h);
}
