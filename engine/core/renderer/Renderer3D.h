//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H


#include "Shader.h"
#include "TexturedModel.h"

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
	};
}// namespace Survive

#endif//SURVIVE_RENDERER3D_H
