//
// Created by david on 16. 05. 2020..
//

#include <fstream>

#include "ObjLoader.h"
#include "../util/Util.h"

Model ObjLoader::loadObj(const char *objFile, Loader &loader)
{
    std::ifstream reader(objFile);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;

    std::string line;
    bool loadingNormals = false;
    while (std::getline(reader, line))
    {
        auto numbers = Util::split(line, ' ');

        if (line.starts_with("vn"))
        {
            float x = std::stof(numbers[1]);
            float y = std::stof(numbers[2]);
            float z = std::stof(numbers[3]);
            normals.emplace_back(x, y, z);
            loadingNormals = true;
        } else if (line.starts_with("vt"))
        {
            float x = std::stof(numbers[1]);
            float y = std::stof(numbers[2]);
            textures.emplace_back(x, y);
        } else if (line.starts_with('v'))
        {
            float x = std::stof(numbers[1]);
            float y = std::stof(numbers[2]);
            float z = std::stof(numbers[3]);
            vertices.emplace_back(x, y, z);
        } else if (loadingNormals)
        {
            if (line.starts_with('f'))
            {
                reader.seekg(-(line.size() + 1), std::ios::cur);
            }
            break;
        }
    }

    return processIndices(reader, loader, vertices, normals, textures);
}

Model ObjLoader::processIndices(std::ifstream &reader, Loader &loader, const std::vector<glm::vec3> &points,
                                const std::vector<glm::vec3> &normals, const std::vector<glm::vec2> &textureCoordinates)
{
    std::vector<float> resultPoints(points.size() * 3);
    std::vector<float> resultNormals(points.size() * 3);
    std::vector<float> resultTextures(points.size() * 2);
    std::vector<unsigned> indices;

    std::string line;
    while (std::getline(reader, line))
    {
        if (line.starts_with('f'))
        {
            auto numbers = Util::split(line, ' ');
            processVertex(points, normals, textureCoordinates, resultPoints, resultNormals, resultTextures, indices,
                          numbers[1]);
            processVertex(points, normals, textureCoordinates, resultPoints, resultNormals, resultTextures, indices,
                          numbers[2]);
            processVertex(points, normals, textureCoordinates, resultPoints, resultNormals, resultTextures, indices,
                          numbers[3]);
        }
    }

    reader.close();
    return loader.loadToVao(resultPoints, indices, resultTextures, resultNormals);
}

void ObjLoader::processVertex(const std::vector<glm::vec3> &points, const std::vector<glm::vec3> &normals,
                              const std::vector<glm::vec2> &textureCoordinates, std::vector<float> &resultPoints,
                              std::vector<float> &resultNormals, std::vector<float> &resultTextures,
                              std::vector<unsigned> &indices, const std::string &line)
{
    auto index = Util::split(line, '/');

    unsigned vertexIndex = std::stoi(index[0]) - 1;
    unsigned textureIndex = std::stoi(index[1]) - 1;
    unsigned normalIndex = std::stoi(index[2]) - 1;

    indices.emplace_back(vertexIndex);

    const auto &point = points[vertexIndex];
    resultPoints[3 * vertexIndex] = point.x;
    resultPoints[3 * vertexIndex + 1] = point.y;
    resultPoints[3 * vertexIndex + 2] = point.z;

    const auto &texture = textureCoordinates[textureIndex];
    resultTextures[2 * vertexIndex] = texture.x;
    resultTextures[2 * vertexIndex + 1] = texture.y;

    const auto &normal = normals[normalIndex];
    resultNormals[3 * vertexIndex] = normal.x;
    resultNormals[3 * vertexIndex + 1] = normal.y;
    resultNormals[3 * vertexIndex + 2] = normal.z;
}
