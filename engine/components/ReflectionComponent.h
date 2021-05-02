//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_REFLECTIONCOMPONENT_H
#define SURVIVE_REFLECTIONCOMPONENT_H

#include "../core/texture/Texture.h"

namespace Survive
{
	struct ReflectionComponent
	{
		Texture reflectionTexture{};
		float reflectionFactor{};

		ReflectionComponent(const Texture &reflectionTexture, float reflectionFactor)
				: reflectionTexture(reflectionTexture), reflectionFactor(reflectionFactor)
		{}

		ReflectionComponent() = default;
	};
}

#endif //SURVIVE_REFLECTIONCOMPONENT_H
