//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAIN_H
#define SURVIVE_TERRAIN_H


#include "../entity/Entity.h"

class Terrain : public Entity
{
public:
    Terrain(const Model &model, const glm::vec3 &position, float scaleX, float scaleY, float scaleZ);

    Terrain() = default;

    void addTextures(const char* blendMap, const std::vector<const char*> &textures);
};


#endif //SURVIVE_TERRAIN_H
