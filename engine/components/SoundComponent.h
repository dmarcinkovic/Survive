//
// Created by david on 01. 04. 2021..
//

#ifndef SURVIVE_SOUNDCOMPONENT_H
#define SURVIVE_SOUNDCOMPONENT_H

#include <AL/al.h>

#include <utility>

#include "Source.h"

namespace Survive
{
	struct SoundComponent
	{
		ALint sound{};

		float pitch = 1.0f, gain = 1.0f;
		bool playOnLoop{};
		bool play = false;

		std::string soundFile{};
		Source audioSource;

		SoundComponent() = default;

		SoundComponent(ALint sound, Source source)
				: sound(sound), audioSource(std::move(source))
		{}

		SoundComponent(ALint sound, Source source, std::string soundFile, float pitch, float gain,
					   bool playOnLoop, bool play)
				: sound(sound), audioSource(std::move(source)), soundFile(std::move(soundFile)), pitch(pitch), gain(gain),
				  playOnLoop(playOnLoop), play(play)
		{}
	};
}

#endif //SURVIVE_SOUNDCOMPONENT_H
