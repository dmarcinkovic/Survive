//
// Created by david on 01. 04. 2021..
//

#ifndef SURVIVE_SOUNDCOMPONENT_H
#define SURVIVE_SOUNDCOMPONENT_H

#include <AL/al.h>

#include "Source.h"

namespace Survive
{
	struct SoundComponent
	{
		ALint sound{};
		float pitch = 1.0f, gain = 1.0f;
		bool playOnLoop{};

		Source audioSource;

		SoundComponent() = default;

		SoundComponent(ALint sound, const Source &source)
				: sound(sound), audioSource(source)
		{}
	};
}

#endif //SURVIVE_SOUNDCOMPONENT_H
