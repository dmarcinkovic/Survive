//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_CAMERA_H
#define SURVIVE_CAMERA_H

#include <glm/glm.hpp>

namespace Survive
{
	class Camera
	{
	private:
		glm::mat4 m_OrthographicProjectionMatrix{};
		glm::mat4 m_ProjectionMatrix{};
		glm::mat4 m_LightProjectionMatrix{};

		glm::mat4 m_ViewMatrix{};

		float m_Pitch{};
		float m_Yaw{};
		glm::vec3 m_Position{};

	public:
		float nearPlane = 0.1f;
		float farPlane = 1000.0f;
		float fieldOfView = 50.0f;

		Camera();

		void invertPitch();

		void moveCameraInYDirection(float yDistance);

		[[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

		[[nodiscard]] const glm::mat4 &getOrthographicProjectionMatrix() const;

		[[nodiscard]] const glm::mat4 &getLightProjectionMatrix() const;

		[[nodiscard]] const glm::mat4 &getViewMatrix() const;

		glm::mat4 &getViewMatrix();

		void recalculateProjectionMatrix(float width, float height);

		[[nodiscard]] float getPitch() const;

		[[nodiscard]] float getYaw() const;

		[[nodiscard]] const glm::vec3 &getPosition() const;

		void setPitch(float pitch);

		void setYaw(float yaw);

		void setPosition(const glm::vec3 &position);

		void setCameraProperties(float pitch, float yaw, const glm::vec3 &position);

	private:
		void recalculateViewMatrix();
	};
}

#endif //SURVIVE_CAMERA_H
