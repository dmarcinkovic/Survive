//
// Created by david on 28. 03. 2022..
//

#include <cmath>
#include <glm/glm.hpp>

#include "ObjectBehaviour.h"
#include "Components.h"

namespace Survive
{
	class ThirdCameraPersonScript : public ObjectBehaviour
	{
	private:
		float m_CameraDistance = 10.0f;
		float m_Angle = 0.0f;

		float m_MouseY = 0.0f;
		float m_MouseX = 0.0f;
		bool m_MouseRightPressed{};
		bool m_MouseLeftPressed{};

	public:
		void update() override
		{
			if (!exists<Transform3DComponent>())
			{
				return;
			}

			Transform3DComponent &transform = getComponent<Transform3DComponent>();
			Camera &camera = getCamera();

			float pitch = glm::radians(camera.pitch);

			float verticalDistance = m_CameraDistance * std::sin(pitch);
			float horizontalDistance = m_CameraDistance * std::cos(pitch);

			updateCameraPosition(camera, transform.position, transform.rotation, verticalDistance, horizontalDistance);
		}

		void onMouseScroll(float offset) override
		{
			m_CameraDistance += offset * 0.5f;
		}

		void onMouseClick(MouseButton mouseButton, MouseAction mouseAction) override
		{
			m_MouseX = getMousePosition().first;
			m_MouseY = getMousePosition().second;

			if (mouseAction == MouseAction::MousePress)
			{
				if (mouseButton == MouseButton::RightButton)
				{
					m_MouseRightPressed = true;
				} else if (mouseButton == MouseButton::LeftButton)
				{
					m_MouseLeftPressed = true;
				}
			} else
			{
				m_MouseLeftPressed = m_MouseRightPressed = false;
			}
		}

		void onMouseMove() override
		{
			if (m_MouseRightPressed)
			{
				float currentMouseY = getMousePosition().second;
				float mouseDy = currentMouseY - m_MouseY;

				float pitchDelta = mouseDy * 0.05f;

				Camera &camera = getCamera();
				camera.pitch -= pitchDelta;
			}

			if (m_MouseLeftPressed)
			{
				float currentMouseX = getMousePosition().first;
				float mouseDx = currentMouseX - m_MouseX;

				float angleDelta = mouseDx * 0.05f;
				m_Angle -= angleDelta;
			}

			m_MouseX = getMousePosition().first;
			m_MouseY = getMousePosition().second;
		}

	private:
		void updateCameraPosition(Camera &camera, const glm::vec3 &position, const glm::vec3 &rotation,
								  float verticalDistance, float horizontalDistance) const
		{
			float theta = glm::radians(rotation.y + m_Angle);

			float offsetX = horizontalDistance * std::sin(theta);
			float offsetZ = horizontalDistance * std::cos(theta);

			camera.position.x = position.x - offsetX;
			camera.position.y = position.y + verticalDistance;
			camera.position.z = position.z - offsetZ;

			camera.yaw = 180 - rotation.y + m_Angle;
		}
	};
}

extern "C" Survive::ObjectBehaviour *create()
{
	return new Survive::ThirdCameraPersonScript();
}

extern "C" void destroy(Survive::ObjectBehaviour *object)
{
	delete object;
}