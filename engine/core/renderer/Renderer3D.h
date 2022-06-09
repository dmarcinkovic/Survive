//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H

#include "Shader.h"
#include "TexturedModel.h"
#include "entt.hpp"

namespace Survive
{
	class Renderer3D
	{
	public:
		static void prepareRendering(const Shader &shader);

		static void finishRendering();

		static void prepareEntity(const TexturedModel &texture, int numberOfVaoUnits);

		static void finishRenderingEntity(int numberOfVaoUnits);

		static void addTransparency(bool cullFace, bool blend);

		static void drawOutline(const entt::registry &registry, entt::entity entity);
	};
}

#endif//SURVIVE_RENDERER3D_H
