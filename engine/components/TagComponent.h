//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_TAGCOMPONENT_H
#define SURVIVE_TAGCOMPONENT_H

#endif //SURVIVE_TAGCOMPONENT_H

namespace Survive
{
	struct TagComponent
	{
		std::string tag{};

		TagComponent() = default;

		explicit TagComponent(const std::string &tag)
				: tag(tag)
		{
		}
	};
}