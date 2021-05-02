//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_RENDERER2DUTIL_H
#define SURVIVE_RENDERER2DUTIL_H


#include "../../shader/Shader.h"
#include "../texture/TexturedModel.h"

namespace Survive
{
	class Renderer2DUtil
	{
	public:
		static void prepareRendering(const Shader &shader);

		static void prepareEntity(const TexturedModel &texture, int numberOfVertexUnits = 2);

		static void finishRenderingEntity(int numberOfVertexUnits = 2);

		static void finishRendering();
	};
}

#endif //SURVIVE_RENDERER2DUTIL_H
