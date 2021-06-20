//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_BLOOMCOMPONENT_H
#define SURVIVE_BLOOMCOMPONENT_H

#include "Texture.h"

namespace Survive
{
	struct BloomComponent
	{
		Texture emissiveTexture{};
		float bloomStrength{};
		Texture bloomTexture{};
		std::string textureName{};

		BloomComponent(const Texture &emissiveTexture, float bloomStrength)
				: emissiveTexture(emissiveTexture), bloomStrength(bloomStrength)
		{}

		BloomComponent() = default;
	};
}

#endif //SURVIVE_BLOOMCOMPONENT_H
