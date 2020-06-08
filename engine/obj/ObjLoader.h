//
// Created by david on 16. 05. 2020..
//

#ifndef SURVIVE_OBJLOADER_H
#define SURVIVE_OBJLOADER_H

#include <glm/glm.hpp>

#include "../renderer/Loader.h"

class ObjLoader
{
private:
    static void processVertex(const std::vector<glm::vec3> &points, const std::vector<glm::vec3> &normals,
                              const std::vector<glm::vec2> &textureCoordinates, std::vector<float> &resultPoints,
                              std::vector<float> &resultNormals, std::vector<float> &resultTextures,
                              const std::string &line);

    static void processIndices(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
                               const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
                               std::vector<float> &resultNormals, std::vector<float> &resultTextures,
                               const std::string &line);

public:
    static Model loadObj(const char *objFile, Loader &loader);
};


#endif //SURVIVE_OBJLOADER_H
