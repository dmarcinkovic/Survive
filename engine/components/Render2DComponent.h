//
// Created by david on 22. 06. 2021..
//

#ifndef SURVIVE_RENDER2DCOMPONENT_H
#define SURVIVE_RENDER2DCOMPONENT_H

#include "TexturedModel.h"

namespace Survive
{
	struct Render2DComponent
	{
		std::string textureName{};
		TexturedModel texturedModel{};

		Render2DComponent() = default;

		explicit Render2DComponent(const TexturedModel &texturedModel)
			: texturedModel(texturedModel)
		{
		}
	};
}

#endif //SURVIVE_RENDER2DCOMPONENT_H
