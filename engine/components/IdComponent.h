//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_IDCOMPONENT_H
#define SURVIVE_IDCOMPONENT_H

#include <cstdint>

namespace Survive
{
	struct IdComponent
	{
		std::uint32_t id;

		IdComponent() = default;

		explicit IdComponent(std::uint32_t id)
				: id(id)
		{}
	};
}

#endif //SURVIVE_IDCOMPONENT_H
