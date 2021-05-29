//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_RENDERCOMPONENT_H
#define SURVIVE_RENDERCOMPONENT_H

#include "TexturedModel.h"

namespace Survive
{
	struct RenderComponent
	{
		std::string modelName{};
		std::string textureName{};

		TexturedModel texturedModel{};

		RenderComponent() = default;

		explicit RenderComponent(const TexturedModel &texturedModel)
				: texturedModel(texturedModel)
		{}
	};
}

#endif //SURVIVE_RENDERCOMPONENT_H
