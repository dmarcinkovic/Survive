//
// Created by david on 01. 04. 2021..
//

#ifndef SURVIVE_SOUNDCOMPONENT_H
#define SURVIVE_SOUNDCOMPONENT_H

#include "Source.h"

namespace Survive
{
	struct SoundComponent
	{
		Source audioSource;

		SoundComponent() = default;

		explicit SoundComponent(const Source &source)
				: audioSource(source)
		{}
	};
}

#endif //SURVIVE_SOUNDCOMPONENT_H
