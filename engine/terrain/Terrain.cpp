//
// Created by david on 22. 05. 2020..
//

#include "Terrain.h"

Terrain::Terrain(const Model &model, const glm::vec3 &position, float scaleX, float scaleY, float scaleZ)
    : Entity(Texture(model, 0), position, scaleX, scaleY, scaleZ)
{

}

void Terrain::addTextures(const char *blendMap, const std::vector<const char *> &textures)
{

}
