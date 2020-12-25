//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYRENDERER_H
#define SURVIVE_SKYRENDERER_H


#include "SkyShader.h"
#include "../entity/Entity.h"
#include "../camera/Camera.h"

class SkyRenderer
{
private:
	SkyShader m_Shader;
	Entity &m_Sky;

public:
	explicit SkyRenderer(Entity &sky);

	void render(const Camera &camera) const;

};


#endif //SURVIVE_SKYRENDERER_H
