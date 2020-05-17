//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTRENDERER_H
#define SURVIVE_OBJECTRENDERER_H


#include <unordered_map>
#include <functional>

#include "ObjectShader.h"
#include "../texture/Texture.h"
#include "../entity/Entity.h"

class ObjectRenderer
{
private:
    ObjectShader m_Shader;
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Entity>>, TextureHash> m_Objects;

public:
    void render() const;

    void add3DObject(Entity &entity);
};


#endif //SURVIVE_OBJECTRENDERER_H
