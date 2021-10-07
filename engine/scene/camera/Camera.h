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
		float NEAR = 0.1f;
		float FAR = 1000.0f;
		float FOV = 70.0f;

		glm::mat4 m_OrthographicProjectionMatrix{};
		glm::mat4 m_ProjectionMatrix{};
		glm::mat4 m_LightProjectionMatrix{};

	public:
		glm::vec3 position{};
		float pitch{};
		float yaw{};

		glm::vec3 rotation{};

		Camera();

		void invertPitch();

		void moveCameraInYDirection(float yDistance);

		[[nodiscard]] glm::mat4 getProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getOrthographicProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getLightProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getViewMatrix() const;

		void recalculateProjectionMatrix(float width, float height);

		[[nodiscard]] float getFar() const;

		[[nodiscard]] float getNear() const;
	};
}

#endif //SURVIVE_CAMERA_H
