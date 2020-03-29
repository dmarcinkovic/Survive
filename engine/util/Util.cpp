//
// Created by david on 29. 03. 2020..
//

#include "Util.h"

std::vector<std::string> Util::split(const std::string &string, const std::string &delimiter)
{
    std::regex pattern(delimiter);
    std::sregex_token_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_token_iterator end;

    std::vector<std::string> result;
    std::copy(begin, end,std::back_inserter(result));

    return result;
}
