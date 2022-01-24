//
// Created by david on 12. 12. 2021..
//

#ifndef SURVIVE_CENTROID_H
#define SURVIVE_CENTROID_H

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include "Camera.h"

namespace Survive
{
	class Centroid
	{
	protected:
		static bool m_CenterHovered;

	protected:
		static void drawCenter(const ImVec2 &center);

		static ImVec2 getCenter(const b2Vec2 &localCenter, const Camera &camera, const glm::vec3 &position,
								const glm::mat4 &modelMatrix, float x, float y, float width, float height);
	};
}


#endif //SURVIVE_CENTROID_H
