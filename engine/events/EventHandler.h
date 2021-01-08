//
// Created by david on 08. 01. 2021..
//

#ifndef SURVIVE_EVENTHANDLER_H
#define SURVIVE_EVENTHANDLER_H


#include "../camera/Camera.h"

class EventHandler
{
private:
	Camera &m_Camera;

	bool m_LeftButtonPressed{};
	bool m_RightButtonPressed{};

	glm::vec2 m_MousePos{};

	glm::vec3 m_CurrentRotation{};
	float m_CurrentYaw{};
	float m_CurrentPitch{};

	bool *m_Active{};

public:
	explicit EventHandler(Camera &camera);

	void registerListener(bool &active);

private:
	void addScrollListener();

	void addMousePressedListener();

	void addMouseMovedListener();

	void addKeyboardListener();
};


#endif //SURVIVE_EVENTHANDLER_H
