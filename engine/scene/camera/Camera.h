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

	public:
		float pitch{};
		float yaw{};
		float near = 0.1f;

		float far = 1000.0f;
		float fieldOfView = 50.0f;

		glm::vec3 rotation{};
		glm::vec3 position{};

		Camera();

		void invertPitch();

		void moveCameraInYDirection(float yDistance);

		[[nodiscard]] glm::mat4 getProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getOrthographicProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getLightProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getViewMatrix() const;

		void recalculateProjectionMatrix(float width, float height);
	};
}

#endif //SURVIVE_CAMERA_H
