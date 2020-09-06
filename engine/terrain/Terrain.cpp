//
// Created by david on 22. 05. 2020..
//

#include "Terrain.h"

Terrain::Terrain(const Model &model, const glm::vec3 &position, float scaleX, float scaleY, float scaleZ)
    : Entity(TexturedModel(model, 0), position, scaleX, scaleY, scaleZ)
{

}
