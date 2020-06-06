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
#include "../light/Light.h"
#include "Object3D.h"

class ObjectRenderer
{
private:
    constexpr static const float fieldOfView = 70.0f;
    constexpr static const float near = 0.1f;
    constexpr static const float far = 1000.0f;

    ObjectShader m_Shader;
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

    const Light &m_Light;

public:
    explicit ObjectRenderer(const Light &light);

    void render(const Camera &camera) const;

    void add3DObject(Object3D &entity);

private:
    void renderScene(const std::vector<std::reference_wrapper<Object3D>> &objects, const Camera &camera) const;
};

#endif //SURVIVE_OBJECTRENDERER_H
