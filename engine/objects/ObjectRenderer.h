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
#include "../camera/Camera.h"

class ObjectRenderer
{
private:
    constexpr static const float fieldOfView = 70.0f;
    constexpr static const float near = 0.1f;
    constexpr static const float far = 1000.0f;

    ObjectShader m_Shader;
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Entity>>, TextureHash> m_Objects;

public:
    ObjectRenderer();

    void render(const Camera &camera) const;

    void add3DObject(Entity &entity);
};


#endif //SURVIVE_OBJECTRENDERER_H
