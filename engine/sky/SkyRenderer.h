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
	static constexpr float ROTATE_SPEED = 5.0f;

	SkyShader m_Shader;
	Entity m_Sky;

	float m_Rotation = 0;

public:
	void render(const Camera &camera) const;

	void addSkyEntity(const Entity &sky);

	void rotateSky();

private:
	void prepareRendering() const;

	static void finishRendering();

	void loadUniforms(const Camera &camera) const;
};


#endif //SURVIVE_SKYRENDERER_H
