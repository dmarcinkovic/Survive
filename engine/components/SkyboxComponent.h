//
// Created by david on 14.06.22..
//

#ifndef SURVIVE_SKYBOXCOMPONENT_H
#define SURVIVE_SKYBOXCOMPONENT_H

#include "TexturedModel.h"
#include "Constants.h"

#include <vector>
#include <string>

namespace Survive
{
	struct SkyboxComponent
	{
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
