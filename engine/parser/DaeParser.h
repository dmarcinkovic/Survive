//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H


#include "../renderer/Loader.h"

class DaeParser
{
public:
    static Model loadDae(const char* daeFile, Loader &loader);
};


#endif //SURVIVE_DAEPARSER_H
