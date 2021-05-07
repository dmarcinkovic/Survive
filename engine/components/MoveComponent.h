//
// Created by david on 11. 03. 2021..
//

#ifndef SURVIVE_MOVECOMPONENT_H
#define SURVIVE_MOVECOMPONENT_H

namespace Survive
{
	struct MoveComponent
	{
		float moveSpeed{};
		float currentMoveValue{};

		MoveComponent() = default;

		explicit MoveComponent(float moveSpeed, float initialMoveValue = 0.0f)
				: moveSpeed(moveSpeed), currentMoveValue(initialMoveValue)
		{}
	};
}

#endif //SURVIVE_MOVECOMPONENT_H
