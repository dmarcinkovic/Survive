//
// Created by david on 17. 05. 2020..
//

#include "ObjectRenderer.h"

void ObjectRenderer::render() const
{

}

void ObjectRenderer::add3DObject(Entity &entity)
{
    std::vector<std::reference_wrapper<Entity>> &batch = m_Objects[entity.m_Texture];
    batch.emplace_back(entity);
}
