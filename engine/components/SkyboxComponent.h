//
// Created by david on 14.06.22..
//

#ifndef SURVIVE_SKYBOXCOMPONENT_H
#define SURVIVE_SKYBOXCOMPONENT_H

#include "TexturedModel.h"
#include "Constants.h"

#include <vector>
#include <string>
#include <bitset>

namespace Survive
{
	struct SkyboxComponent
	{
	private:
		friend class ComponentLoader;

		template<typename ComponentType> friend
		class ComponentTemplate;

		bool m_ModelLoaded{};
		std::bitset<Constants::NUMBER_OF_FACES> m_LoadedTextures{};

	public:

		TexturedModel skyboxModel;
		std::vector<std::string> faces;

		SkyboxComponent()
				: faces(Constants::NUMBER_OF_FACES)
		{}

		explicit SkyboxComponent(std::vector<std::string> faces)
				: faces(std::move(faces))
		{}
	};
}

#endif //SURVIVE_SKYBOXCOMPONENT_H
