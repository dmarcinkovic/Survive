//
// Created by david on 06. 06. 2020..
//

#ifndef SURVIVE_CONSTANTS_H
#define SURVIVE_CONSTANTS_H

struct Constants
{
	constexpr static float NEAR = 0.1f;
	constexpr static float FAR = 1000.0f;
	constexpr static float LEFT = -10.0f;
	constexpr static float RIGHT = 40.0f;
	constexpr static float BOTTOM = -10.0f;
	constexpr static float TOP = 40.0f;
	constexpr static float FOV = 70.0f;
	constexpr static const int SHADOW_WIDTH = 1024;
	constexpr static const int SHADOW_HEIGHT = 1024;
	constexpr static double GRAVITY = -50;
	constexpr const static glm::vec4 CLEAR_COLOR{0.5f, 0.5f, 0.5f, 1.0f};
	constexpr static float WATER_HEIGHT = -6;
};

#endif //SURVIVE_CONSTANTS_H
