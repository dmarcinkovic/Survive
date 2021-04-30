//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_REFRACTIONCOMPONENT_H
#define SURVIVE_REFRACTIONCOMPONENT_H

#include "../texture/Texture.h"

struct RefractionComponent
{
	Texture refractionTexture{};
	float refractiveIndex{};
	float refractiveFactor{};

	RefractionComponent(const Texture &refractionTexture, float refractiveIndex, float refractiveFactor)
			: refractionTexture(refractionTexture), refractiveIndex(refractiveIndex), refractiveFactor(refractiveFactor)
	{}

	RefractionComponent() = default;
};

#endif //SURVIVE_REFRACTIONCOMPONENT_H
