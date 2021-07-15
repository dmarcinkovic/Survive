//
// Created by david on 15. 07. 2021..
//

#include "Components.h"
#include "AudioSystem.h"

void Survive::AudioSystem::update(entt::registry &registry)
{
	auto view = registry.view<SoundComponent>();

	for (auto const &entity : view)
	{
		SoundComponent &soundComponent = view.get<SoundComponent>(entity);
		Source &source = soundComponent.audioSource;

		if (registry.has<Transform3DComponent>(entity))
		{
			const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
			source.setPosition(transform.position);
		}

		if (!source.isPlaying())
		{
			source.play(soundComponent.sound);
		}
	}
}
