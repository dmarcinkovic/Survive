//
// Created by david on 16. 05. 2020..
//

#ifndef SURVIVE_OBJLOADER_H
#define SURVIVE_OBJLOADER_H


#include "../renderer/Loader.h"

class ObjLoader
{
public:
    static Model loadObj(const char* objFile);
};


#endif //SURVIVE_OBJLOADER_H
