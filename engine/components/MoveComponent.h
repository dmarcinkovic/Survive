//
// Created by david on 11. 03. 2021..
//

#ifndef SURVIVE_MOVECOMPONENT_H
#define SURVIVE_MOVECOMPONENT_H

struct MoveComponent
{
	float moveSpeed{};
	float currentMoveValue{};

	MoveComponent() = default;

	explicit MoveComponent(float moveSpeed)
			: moveSpeed(moveSpeed)
	{}
};

#endif //SURVIVE_MOVECOMPONENT_H
