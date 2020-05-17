//
// Created by david on 17. 05. 2020..
//

#include "../display/Display.h"
#include "Camera.h"

Camera::Camera()
{
    addScrollListener();
    addMousePressedListener();
    addMouseMovedListener();
}

void Camera::addScrollListener()
{
    auto scrollListener = [this](double xOffset, double yOffset)
    {
        m_Position.z -= yOffset * 2.0;
    };
    Display::addScrollListener(scrollListener);
}

void Camera::addMousePressedListener()
{
    auto mousePressedListener = [this](int button, int action, double mouseX, double mouseY)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            m_MousePressed = true;
            m_MousePos = glm::vec2{mouseX, mouseY};
            m_CurrentRotation = m_Rotation;
        } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            m_MousePressed = false;
        }
    };
    Display::addMouseListener(mousePressedListener);
}

void Camera::addMouseMovedListener()
{
    auto mouseMovedListener = [this](double mouseX, double mouseY)
    {
        if (!m_MousePressed) return;

        double dx = mouseX - m_MousePos.x;
        double dy = mouseY - m_MousePos.y;

        m_Rotation.x = m_CurrentRotation.x + dy / 2.0;
        m_Rotation.y = m_CurrentRotation.y + dx / 2.0;
    };
    Display::addMouseMovedListener(mouseMovedListener);
}
