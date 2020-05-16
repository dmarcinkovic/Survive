//
// Created by david on 16. 05. 2020..
//

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>

#include "ObjLoader.h"
#include "../util/Util.h"

Model ObjLoader::loadObj(const char *objFile)
{
    std::ifstream reader(objFile);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;

    std::string line;
    while (std::getline(reader, line))
    {
        auto numbers = Util::split(line, ' ');

        if (line.starts_with("vn"))
        {
            float x = std::stof(numbers[1]);
            float y = std::stof(numbers[2]);
            float z = std::stof(numbers[3]);
            normals.emplace_back(x, y, z);
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
        } else if (line.starts_with('f'))
        {

        }
    }
    return Model(0, 0);
}
