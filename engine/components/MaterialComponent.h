//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_MATERIALCOMPONENT_H
#define SURVIVE_MATERIALCOMPONENT_H

#include "Texture.h"
#include "entt.hpp"

namespace Survive
{
	struct MaterialComponent
	{
		bool isTransparent{};
		bool useNormalMapping{};
		Texture normalMap{};

		entt::entity skyboxEntity = entt::null;
		std::string skyboxEntityName = "none";

		std::string normalMapPath{};

		explicit MaterialComponent(bool isTransparent, bool useNormalMapping = false, Texture normalMap = Texture{})
				: isTransparent(isTransparent), useNormalMapping(useNormalMapping), normalMap(normalMap)
		{}

		MaterialComponent() = default;
	};
}

#endif //SURVIVE_MATERIALCOMPONENT_H
