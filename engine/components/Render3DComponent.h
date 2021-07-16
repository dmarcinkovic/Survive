//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_RENDER3DCOMPONENT_H
#define SURVIVE_RENDER3DCOMPONENT_H

#include <string>

#include "TexturedModel.h"

namespace Survive
{
	struct Render3DComponent
	{
		std::string modelName{};
		std::string textureName{};

		TexturedModel texturedModel{};

		Render3DComponent() = default;

		explicit Render3DComponent(const TexturedModel &texturedModel)
				: texturedModel(texturedModel)
		{}
	};
}

#endif //SURVIVE_RENDER3DCOMPONENT_H
