//
// Created by david on 06. 06. 2020..
//

#ifndef SURVIVE_CONSTANTS_H
#define SURVIVE_CONSTANTS_H

#include <glm/vec4.hpp>

namespace Survive
{
	struct Constants
	{
		constexpr static float LEFT = -10.0f;
		constexpr static float RIGHT = 40.0f;
		constexpr static float BOTTOM = -10.0f;
		constexpr static float TOP = 40.0f;
		constexpr static const int SHADOW_WIDTH = 1024;
		constexpr static const int SHADOW_HEIGHT = 1024;
		constexpr static float GRAVITY = -50.0f;
		constexpr const static glm::vec4 CLEAR_COLOR{0.5f, 0.5f, 0.5f, 1.0f};
		constexpr static float WATER_HEIGHT = -6;
		constexpr static int BLOOM_WIDTH = 100;
		constexpr static int BLOOM_HEIGHT = 100;
	};
}

#endif //SURVIVE_CONSTANTS_H
