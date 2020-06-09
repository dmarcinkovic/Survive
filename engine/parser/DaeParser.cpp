//
// Created by david on 09. 06. 2020..
//

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include "DaeParser.h"
#include "../util/Util.h"

Model DaeParser::loadDae(const char *daeFile, Loader &loader)
{
    std::ifstream reader(daeFile);

    Model model;

    std::string line;
    while (std::getline(reader, line))
    {
        if (line.find("<library_geometries>") != -1)
        {
            model = loadGeometry(reader, loader);
        }
    }

    reader.close();
    return model;
}

Model DaeParser::loadGeometry(std::ifstream &reader, Loader &loader)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;

    std::string line;
    while (std::getline(reader, line))
    {
        if (line.find(R"(id="Cube-mesh-positions-array")") != -1)
        {
            parsePointsLine(line, vertices);
        } else if (line.find(R"(id="Cube-mesh-normals-array")") != -1)
        {
            parsePointsLine(line, normals);
        } else if (line.find(R"(id="Cube-mesh-map-0-array")") != -1)
        {
            parseTexturesLine(line, textures);
        } else if (line.find("<p>") != -1)
        {
            return parseIndices(loader, line, vertices, normals, textures);
        } else if (line.find("</library_geometries>") != -1)
        {
            break;
        }
    }

    return Model(0, 0);
}

void DaeParser::parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices)
{
    int index = line.find('>');
    auto numbers = Util::split(line.substr(index + 1), ' ');

    for (int i = 0; i < numbers.size(); i += 3)
    {
        float x = std::stof(numbers[i]);
        float y = std::stof(numbers[i + 1]);
        float z = std::stof(numbers[i + 2]);
        vertices.emplace_back(x, y, z);
    }
}

void DaeParser::parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures)
{
    int index = line.find('>');
    auto numbers = Util::split(line.substr(index + 1), ' ');

    for (int i = 0; i < numbers.size(); i += 2)
    {
        float x = std::stof(numbers[i]);
        float y = std::stof(numbers[i + 1]);
        textures.emplace_back(x, y);
    }
}

Model DaeParser::parseIndices(Loader &loader, std::string &line, const std::vector<glm::vec3> &vertices,
                              const std::vector<glm::vec3> &normals, const std::vector<glm::vec2> &textures)
{
    int index = line.find('>');
    auto numbers = Util::split(line.substr(index + 1), ' ');

    std::vector<float> resultPoints;
    std::vector<float> resultNormals;
    std::vector<float> resultTextures;

    for (int i = 0; i < numbers.size(); i += 3)
    {
        unsigned vertexIndex = std::stoi(numbers[i]);
        unsigned textureIndex = std::stoi(numbers[i + 1]);
        unsigned normalIndex = std::stoi(numbers[i + 2]);

        Util::processVertex(vertices, normals, textures,
                            resultPoints, resultNormals, resultTextures,
                            vertexIndex, textureIndex, normalIndex);
    }

    return loader.loadToVao(resultPoints, resultTextures, resultNormals);
}
