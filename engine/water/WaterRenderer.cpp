//
// Created by david on 22. 02. 2021..
//

#include "WaterRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

WaterRenderer::WaterRenderer()
{

}

void WaterRenderer::render(const Camera &camera, const Light &light) const
{
	prepareRendering(camera);

	for (auto const &waterTile : m_Tiles)
	{
		auto const &water = waterTile.get();


	}

	finishRendering();
}

void WaterRenderer::prepareRendering(const Camera &camera) const
{
	Renderer3DUtil::prepareRendering(m_Shader);
	glEnableVertexAttribArray(0);
	Renderer3DUtil::addTransparency(true, true);

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
}

void WaterRenderer::finishRendering()
{
	TexturedModel::unbindVao();
	glDisableVertexAttribArray(0);
	Renderer3DUtil::addTransparency(false, false);
	Renderer3DUtil::finishRendering();
}
