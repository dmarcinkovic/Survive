//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_REFLECTIONCOMPONENT_H
#define SURVIVE_REFLECTIONCOMPONENT_H

#include "Texture.h"

namespace Survive
{
	struct ReflectionComponent
	{
		float reflectionFactor{};

		explicit ReflectionComponent(float reflectionFactor)
				: reflectionFactor(reflectionFactor)
		{}

		ReflectionComponent() = default;
	};
}

#endif //SURVIVE_REFLECTIONCOMPONENT_H
