//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTYPE_H
#define SURVIVE_COMPONENTTYPE_H

#include <string>
#include <vector>
#include <variant>

#include "Components.h"

namespace Survive
{
	class ComponentList
	{
	public:
		static std::vector<const char *> getListOfComponents()
		{
			std::vector<const char *> components = {
					"Animation component", "Bloom component", "Move component",
					"Reflection component", "Refraction component", "Render component",
					"Rigid body component", "Shadow component", "Sound component",
					"Sprite component", "Sprite sheet component", "Textured component",
					"Transform2D component", "Transform3D component"
			};

			return components;
		}
	};
}

#endif //SURVIVE_COMPONENTTYPE_H
