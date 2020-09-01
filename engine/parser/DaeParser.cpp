//
// Created by david on 09. 06. 2020..
//

#include <fstream>
#include <iostream>

#include "DaeParser.h"
#include "../util/Util.h"

VertexData DaeParser::vertexData;

Model DaeParser::loadDae(const char *daeFile, Loader &loader)
{
    std::ifstream reader(daeFile);
    std::vector<std::string> jointNames;

    std::string line;
    while (std::getline(reader, line))
    {
        if (line.find("<library_geometries>") != -1)
        {
            loadGeometry(reader);
        } else if (line.find("<library_controllers>") != -1)
        {
            loadControllers(reader, jointNames);
        } else if (line.find("<library_visual_scenes>") != -1)
        {
            loadVisualScene(reader, jointNames);
        }
    }

    std::cout << "Joint names are:\n";
    for (auto const &name : jointNames)
    {
        std::cout << name << '\n';
    }

    reader.close();
    return parseIndices(loader);
}

void DaeParser::loadGeometry(std::ifstream &reader)
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
            vertexData.indicesLine = line;
            vertexData.size = coordinatesSize + 1;
            vertexData.vertices = vertices;
            vertexData.textures = textures;
            vertexData.normals = normals;
            break;
        } else if (line.find("input semantic") != -1)
        {
            int index = line.find("offset");
            if (index != -1)
            {
                char c = line[index + 8];
                coordinatesSize = c - '0';
            }
        }
    }
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

Model DaeParser::parseIndices(Loader &loader)
{
    int index = vertexData.indicesLine.find('>');
    auto numbers = Util::split(vertexData.indicesLine.substr(index + 1), ' ');

    std::vector<float> resultPoints;
    std::vector<float> resultNormals;
    std::vector<float> resultTextures;
    std::vector<float> resultWeights;
    std::vector<unsigned> resultIds;

    for (int i = 0; i < numbers.size(); i += vertexData.size)
    {
        unsigned vertexIndex = std::stoi(numbers[i]);
        unsigned normalIndex = std::stoi(numbers[i + 1]);
        unsigned textureIndex = std::stoi(numbers[i + 2]);

        Util::processVertex(vertexData.vertices, vertexData.normals, vertexData.textures,
                            resultPoints, resultNormals, resultTextures,
                            vertexIndex, textureIndex, normalIndex);

        processJointsData(resultWeights, resultIds, vertexIndex);
    }

    return loader.loadToVao(resultPoints, resultTextures, resultNormals, resultWeights, resultIds);
}

void DaeParser::loadControllers(std::ifstream &reader, std::vector<std::string> &jointNames)
{
    std::vector<float> weights;
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

            int index = 0;
            for (int n : count)
            {
                int numberOfJoints = std::min(n, 3);

                glm::vec3 jointWeight{-1, -1, -1};
                glm::ivec3 jointId{-1, -1, -1};
                for (int i = 0; i < 2 * numberOfJoints; i += 2)
                {
                    int j = i / 2;
                    jointId[j] = std::stoi(numbers[index++]);
                    jointWeight[j] = weights[std::stof(numbers[index++])];
                }

                jointIds.emplace_back(jointId);
                jointWeights.emplace_back(jointWeight);

                if (n > numberOfJoints)
                {
                    index += 2 * (n - numberOfJoints);
                }
            }

            vertexData.jointWeights = jointWeights;
            vertexData.jointIds = jointIds;
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

void DaeParser::processJointsData(std::vector<float> &resultWeights, std::vector<unsigned int> &resultIds,
                                  unsigned int index)
{
    const auto &weight = vertexData.jointWeights[index];
    resultWeights.emplace_back(weight.x);
    resultWeights.emplace_back(weight.y);
    resultWeights.emplace_back(weight.z);

    const auto &id = vertexData.jointIds[index];
    resultWeights.emplace_back(id.x);
    resultWeights.emplace_back(id.y);
    resultWeights.emplace_back(id.z);
}

void DaeParser::loadVisualScene(std::ifstream &reader, const std::vector<std::string> &jointNames)
{
    static const int OFFSET = 4;

    std::string line;
    while (std::getline(reader, line))
    {
        if (line.find("type=\"JOINT\"") != -1)
        {
            const int startIndex = line.find("id=");
            std::string restOfLine = line.substr(startIndex + OFFSET);
            const int length = restOfLine.find('\"');

            std::string name = restOfLine.substr(0, length);
            int index = std::find(jointNames.begin(), jointNames.end(), name) - jointNames.begin();

            std::getline(reader, line);

            Joint joint(name, index, getJointTransform(line));
        }
    }
}

glm::mat4 DaeParser::getJointTransform(std::string &line)
{
    auto data = getData(line);
    glm::mat4 transform{};

    static const int SIZE = 4;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int index = i * SIZE + j;
            transform[i][j] = std::stof(data[index]);
        }
    }

    return transform;
}
