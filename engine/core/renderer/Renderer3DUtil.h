//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_RENDERER3DUTIL_H
#define SURVIVE_RENDERER3DUTIL_H


#include "../texture/TexturedModel.h"
#include "../shader/Shader.h"

namespace Survive
{
	class Renderer3DUtil
	{
	public:
		static void prepareRendering(const Shader &shader);

		static void finishRendering();

		static void prepareEntity(const TexturedModel &texture);

		static void finishRenderingEntity();

		static void addTransparency(bool cullFace, bool blend);
	};
}

#endif //SURVIVE_RENDERER3DUTIL_H
