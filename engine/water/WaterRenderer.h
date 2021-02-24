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

class WaterRenderer
{
private:
	static constexpr float WAVE_SPEED = 0.03f;

	WaterShader m_Shader;

	std::vector<std::reference_wrapper<WaterTile>> m_Tiles;

public:
	void render(const Camera &camera, const Light &light, const Texture &reflectionTexture,
				const Texture &refractionTexture) const;

	void addWaterTile(WaterTile &waterTile);

	[[nodiscard]] bool shouldRender() const;

private:
	void prepareRendering(const Camera &camera) const;

	static void finishRendering();

	static void loadMoveFactor(const WaterShader &shader);

	void loadUniforms(const Camera &camera, const WaterTile &waterTile) const;

	static void
	bindTextures(const WaterTile &waterTile, const Texture &reflectionTexture, const Texture &refractionTexture);
};


#endif //SURVIVE_WATERRENDERER_H
