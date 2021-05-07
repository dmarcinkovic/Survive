//
// Created by david on 29. 03. 2021..
//

#include "SkyRotateSystem.h"
#include "../../components/MoveComponent.h"
#include "../../core/display/Display.h"

void Survive::SkyRotateSystem::rotateSky(entt::registry &registry, entt::entity sky)
{
	MoveComponent &moveComponent = registry.get<MoveComponent>(sky);

	auto deltaTime = static_cast<float>(Display::getFrameTime());
	moveComponent.currentMoveValue += moveComponent.moveSpeed * deltaTime;
}
