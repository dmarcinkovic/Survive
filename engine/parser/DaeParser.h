//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H

#include <glm/glm.hpp>
#include <vector>

#include "../renderer/Loader.h"

struct VertexData
{
    std::string indicesLine;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;

    std::vector<glm::ivec3> jointIds;
    std::vector<glm::vec3> jointWeights;

    int size;
};

class DaeParser
{
private:
    static VertexData vertexData;

    static void loadGeometry(std::ifstream &reader);

    static void parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices);

    static void parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures);

    static Model parseIndices(Loader &loader, std::string &line, const std::vector<glm::vec3> &vertices,
                              const std::vector<glm::vec3> &normals, const std::vector<glm::vec2> &textures, int size);

    static void loadControllers(std::ifstream &reader);

    static std::vector<std::string> getData(std::string &line);

public:
    static Model loadDae(const char *daeFile, Loader &loader);
};


#endif //SURVIVE_DAEPARSER_H
