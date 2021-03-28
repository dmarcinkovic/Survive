//
// Created by david on 29. 03. 2021..
//

#include <iostream>
#include "SkyRotateSystem.h"
#include "../display/Display.h"
#include "../components/MoveComponent.h"

void SkyRotateSystem::rotateSky(entt::registry &registry, entt::entity sky)
{
	MoveComponent &moveComponent = registry.get<MoveComponent>(sky);

	auto deltaTime = static_cast<float>(Display::getFrameTime());
	moveComponent.currentMoveValue += moveComponent.moveSpeed * deltaTime;
}
