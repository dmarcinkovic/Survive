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
		glm::mat4 m_ProjectionMatrix{};
		glm::mat4 m_OrthographicProjectionMatrix{};

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

		[[nodiscard]] glm::mat4 getViewMatrix() const;

		void recalculateProjectionMatrix(float width, float height);
	};
}

#endif //SURVIVE_CAMERA_H
