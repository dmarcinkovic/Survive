//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTRENDERER_H
#define SURVIVE_TEXTRENDERER_H

#include <functional>
#include <unordered_set>

#include "entt.hpp"
#include "TextShader.h"
#include "Text.h"
#include "Camera.h"

namespace Survive
{
	class TextRenderer
	{
	private:
		TextShader m_Shader{};

	public:
		void renderText(entt::registry &registry, const Camera &camera) const;

	private:
		void loadUniforms(entt::registry &registry, entt::entity entity) const;
	};
}

#endif //SURVIVE_TEXTRENDERER_H
