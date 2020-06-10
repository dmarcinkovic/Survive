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
        } else if (line.find("<library_controllers>") != -1)
        {
            loadControllers(reader);
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

    int coordinatesSize = 0;

    std::string line;
    while (std::getline(reader, line))
    {
        if (vertices.empty() && line.find("positions-array") != -1)
        {
            parsePointsLine(line, vertices);
        } else if (normals.empty() && line.find("normals-array") != -1)
        {
            parsePointsLine(line, normals);
        } else if (textures.empty() && line.find("map-0-array") != -1)
        {
            parseTexturesLine(line, textures);
        } else if (line.find("<p>") != -1)
        {
            return parseIndices(loader, line, vertices, normals, textures, coordinatesSize + 1);
        } else if (line.find("input semantic") != -1)
        {
            int index = line.find("offset");
            if (index != -1)
            {
                char c = line[index + 8];
                coordinatesSize = c - '0';
            }
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
                              const std::vector<glm::vec3> &normals, const std::vector<glm::vec2> &textures, int size)
{
    int index = line.find('>');
    auto numbers = Util::split(line.substr(index + 1), ' ');

    std::vector<float> resultPoints;
    std::vector<float> resultNormals;
    std::vector<float> resultTextures;

    for (int i = 0; i < numbers.size(); i += size)
    {
        unsigned vertexIndex = std::stoi(numbers[i]);
        unsigned normalIndex = std::stoi(numbers[i + 1]);
        unsigned textureIndex = std::stoi(numbers[i + 2]);

        Util::processVertex(vertices, normals, textures,
                            resultPoints, resultNormals, resultTextures,
                            vertexIndex, textureIndex, normalIndex);
    }

    return loader.loadToVao(resultPoints, resultTextures, resultNormals);
}

void DaeParser::loadControllers(std::ifstream &reader)
{
    std::vector<float> weights;
    std::vector<std::string> jointNames;
    std::vector<int> count;
    std::vector<glm::ivec3> jointIds;
    std::vector<glm::vec3> jointWeights;

    std::string line;
    while (std::getline(reader, line))
    {
        if (jointNames.empty() && line.find("skin-joints-array") != -1)
        {
            jointNames = getData(line);
        } else if (weights.empty() && line.find("skin-weights-array") != -1)
        {
            auto numbers = getData(line);
            weights.reserve(numbers.size());

            for (auto const &weight : numbers)
            {
                weights.emplace_back(std::stof(weight));
            }
        } else if (count.empty() && line.find("<vcount>") != -1)
        {
            auto numbers = getData(line);
            count.reserve(numbers.size());

            for (auto const &c : numbers)
            {
                count.emplace_back(std::stoi(c));
            }
        } else if (line.find("<v>") != -1)
        {
            auto numbers = getData(line);

            jointWeights.reserve(count.size());
            jointIds.reserve(count.size());

            int index = 0;
            for (int n : count)
            {
                if (n <= 3)
                {
                    glm::vec3 jointWeight{-1, -1, -1};
                    glm::ivec3 jointId{-1, -1, -1};
                    for (int i = 0; i < 2 * n; i += 2)
                    {
                        int j = i / 2;
                        jointId[j] = std::stoi(numbers[index++]);
                        jointWeight[j] = weights[std::stof(numbers[index++])];
                    }

                    jointIds.emplace_back(jointId);
                    jointWeights.emplace_back(jointWeight);
                } else
                {
                    index += 2;
                }
            }

            for (auto &jointId : jointIds)
            {
                std::cout << jointId.x << ' ' << jointId.y << ' ' << jointId.z << '\n';
            }

            break;
        }
    }
}

std::vector<std::string> DaeParser::getData(std::string &line)
{
    int start = line.find('>');
    int end = line.find_last_of('<');

    if (end == -1)
    {
        end = line.length();
    }

    return Util::split(line.substr(start + 1, end - start - 1), ' ');
}
