//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_RIGIDBODYCOMPONENT_H
#define SURVIVE_RIGIDBODYCOMPONENT_H

namespace Survive
{
	struct RigidBodyComponent
	{
		bool isTransparent{};

		explicit RigidBodyComponent(bool isTransparent)
				: isTransparent(isTransparent)
		{}

		RigidBodyComponent() = default;
	};
}

#endif //SURVIVE_RIGIDBODYCOMPONENT_H
