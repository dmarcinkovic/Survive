//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H

#include <glm/glm.hpp>
#include <vector>

#include "../renderer/Loader.h"
#include "../animation/joints/Joint.h"

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

    static void loadVisualScene(std::ifstream &reader, const std::vector<std::string> &jointNames);

    static void parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices);

    static void parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures);

    static Model parseIndices(Loader &loader);

    static void loadControllers(std::ifstream &reader, std::vector<std::string> &jointNames);

    static std::vector<std::string> getData(std::string &line);

    static void processJointsData(std::vector<float> &resultWeights, std::vector<unsigned> &resultIds, unsigned index);

public:
    static Model loadDae(const char *daeFile, Loader &loader);
};


#endif //SURVIVE_DAEPARSER_H
