//
// Created by david on 27. 12. 2020..
//

#ifndef SURVIVE_OUTLINERENDERER_H
#define SURVIVE_OUTLINERENDERER_H

#include <functional>
#include <unordered_map>

#include "entt.hpp"
#include "OutlineShader.h"
#include "Transform3DComponent.h"
#include "Render3DComponent.h"
#include "Camera.h"
#include "Renderer3D.h"

namespace Survive
{
	class OutlineRenderer : public Renderer3D
	{
	private:
		static constexpr float SCALE = 1.01f;

		OutlineShader m_Shader;

	public:
		void render(entt::registry &registry, const Camera &camera) const;

	private:
		static void setStencilFunctions();

		static void resetStencilFunctions();

		void loadUniforms(const Transform3DComponent &transform, const Camera &camera) const;

		static void prepareObject(const Render3DComponent &renderComponent);

		static void finishRenderingObject();
	};
}


#endif //SURVIVE_OUTLINERENDERER_H
