//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_CAMERA_H
#define SURVIVE_CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 m_Position{};
	float m_Pitch{};
	float m_Yaw{};

	glm::vec3 m_Rotation{};

	Camera();

	void invertPitch();

private:
	bool m_LeftButtonPressed{};
	bool m_RightButtonPressed{};

	glm::vec2 m_MousePos{};
	glm::vec3 m_CurrentRotation{};
	float m_CurrentYaw{};
	float m_CurrentPitch{};

	void addScrollListener();

	void addMousePressedListener();

	void addMouseMovedListener();

	void addKeyboardListener();
};


#endif //SURVIVE_CAMERA_H
