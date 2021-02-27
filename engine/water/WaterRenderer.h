//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERRENDERER_H
#define SURVIVE_WATERRENDERER_H

#include <functional>

#include "../texture/Texture.h"
#include "WaterShader.h"
#include "WaterTile.h"
#include "../light/Light.h"
#include "../camera/Camera.h"
#include "WaterFbo.h"

class WaterRenderer
{
private:
	static constexpr float WAVE_SPEED = 0.03f;

	WaterShader m_Shader;
	WaterFbo m_Fbo;

	std::vector<std::reference_wrapper<WaterTile>> m_Tiles;

public:
	void render(const Camera &camera, const Light &light) const;

	void addWaterTile(WaterTile &waterTile);

	void bindReflectionFrameBuffer() const;

	void bindRefractionFrameBuffer() const;

	[[nodiscard]] bool shouldRender() const;

private:
	void prepareRendering(const Camera &camera) const;

	static void finishRendering();

	static void loadMoveFactor(const WaterShader &shader);

	void loadUniforms(const Camera &camera, const WaterTile &waterTile, const Light &light) const;

	static void
	bindTextures(const WaterTile &waterTile, const Texture &reflectionTexture, const Texture &refractionTexture,
				 const Texture &refractionDepthMap);
};


#endif //SURVIVE_WATERRENDERER_H
