//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H


#include "../renderer/Loader.h"

class DaeParser
{
private:
    static Model loadGeometry(std::ifstream &reader, Loader &loader);

    static void parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices);

    static void parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures);

    static Model parseIndices(Loader &loader, std::string &line, const std::vector<glm::vec3> &vertices,
                              const std::vector<glm::vec3> &normals, const std::vector<glm::vec2> &textures, int size);

public:
    static Model loadDae(const char *daeFile, Loader &loader);
};


#endif //SURVIVE_DAEPARSER_H
