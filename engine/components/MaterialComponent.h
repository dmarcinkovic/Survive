//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_MATERIALCOMPONENT_H
#define SURVIVE_MATERIALCOMPONENT_H

namespace Survive
{
	struct MaterialComponent
	{
		bool isTransparent{};

		explicit MaterialComponent(bool isTransparent)
				: isTransparent(isTransparent)
		{}

		MaterialComponent() = default;
	};
}

#endif //SURVIVE_MATERIALCOMPONENT_H
