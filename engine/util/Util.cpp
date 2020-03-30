//
// Created by david on 29. 03. 2020..
//

#include <cmath>

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

float Util::getNumber(const std::string &string, char delimiter)
{
    int index = string.find(delimiter);
    return std::stof(string.substr(index + 1));
}

Character Util::getCharacterFromFntFile(const std::vector<std::string> &line, float w, float h)
{
    int id = std::floor(getNumber(line[1]));
    float x = getNumber(line[2]);
    float y = getNumber(line[3]);
    float width = getNumber(line[4]);
    float height = getNumber(line[5]);
    float xOffset = getNumber(line[6]);
    float yOffset = -getNumber(line[7]);
    float advance = getNumber(line[8]);

    return Character(id, x, y, width, height, xOffset, yOffset, advance, w, h);
}

std::optional<Character> Util::getCharacterFromJsonFile(const std::string &line, float scaleW, float scaleH)
{
    std::string pattern = R"(\s+\"(.?.?)\":\{\"x\":(\d+),\"y\":(\d+),\"width\":(\d+),\"height\")"
                          R"(:(\d+),\"originX\":(-?\d+),\"originY\":(-?\d+),\"advance\":(\d+))";
    std::regex regex(pattern);
    std::smatch result;
    std::regex_search(line, result, regex);

    if (result.empty())
    {
        return {};
    }

    return getCharacterFromJsonFile(result, scaleW, scaleH);
}

Character Util::getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH)
{
    int id = result[1].str().length() == 2 ? result[1].str()[1] : result[1].str()[0];
    float x = std::stof(result[2].str());
    float y = std::stof(result[3].str());
    float width = std::stof(result[4].str());
    float height = std::stof(result[5].str());
    float xOffset = std::stof(result[6].str());
    float yOffset = std::stof(result[7].str());
    float advance = std::stof(result[8].str());

    return Character(id, x, y, width, height, xOffset, yOffset, advance, scaleW, scaleH);
}

