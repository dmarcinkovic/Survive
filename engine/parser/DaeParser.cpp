//
// Created by david on 09. 06. 2020..
//

#include <fstream>
#include "DaeParser.h"

Model DaeParser::loadDae(const char *daeFile, Loader &loader)
{
    std::ifstream reader(daeFile);

    std::string line;
    while(std::getline(reader, line))
    {
        
    }

    reader.close();
    return Model(0, 0);
}
