//
// Created by david on 09. 04. 2021..
//

#ifndef SURVIVE_SHADOWCOMPONENT_H
#define SURVIVE_SHADOWCOMPONENT_H

struct ShadowComponent
{
	bool loadShadow;

	explicit ShadowComponent(bool loadShadow)
			: loadShadow(loadShadow)
	{}

	ShadowComponent() = default;
};

#endif //SURVIVE_SHADOWCOMPONENT_H
