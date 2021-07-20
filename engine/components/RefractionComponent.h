//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_REFRACTIONCOMPONENT_H
#define SURVIVE_REFRACTIONCOMPONENT_H


namespace Survive
{
	struct RefractionComponent
	{
		float refractiveIndex{};
		float refractiveFactor{};

		RefractionComponent(float refractiveIndex, float refractiveFactor)
				: refractiveIndex(refractiveIndex), refractiveFactor(refractiveFactor)
		{}

		RefractionComponent() = default;
	};
}

#endif //SURVIVE_REFRACTIONCOMPONENT_H
