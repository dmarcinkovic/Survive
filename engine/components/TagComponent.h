//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_TAGCOMPONENT_H
#define SURVIVE_TAGCOMPONENT_H

#include <string>
#include <utility>

namespace Survive
{
	struct TagComponent
	{
		std::string tag{};

		TagComponent() = default;

		explicit TagComponent(std::string tag)
				: tag(std::move(tag))
		{
		}
	};
}

#endif //SURVIVE_TAGCOMPONENT_H