//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_RENDERER2D_H
#define SURVIVE_RENDERER2D_H

#include <vector>

#include "../shader/Shader.h"
#include "../entity/Entity2D.h"

class Renderer2D
{
private:
    Shader m_Shader;

    void prepareRendering(const Entity2D &entity2D);

    static void finishRendering();

public:
    explicit Renderer2D(const Shader &shader);

    void render(const std::vector<Entity2D> &entities);
};


#endif //SURVIVE_RENDERER2D_H
