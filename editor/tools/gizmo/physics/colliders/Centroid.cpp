//
// Created by david on 12. 12. 2021..
//

#include "Centroid.h"
#include "Constants.h"
#include "Util.h"

bool Survive::Centroid::m_CenterHovered{};

void Survive::Centroid::drawCenter(const ImVec2 &center)
{
	static constexpr ImU32 COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = m_CenterHovered ? COLOR_HOVERED : COLOR;
	drawList->AddCircle(center, 4.0, color, 0, 2.0f);
}

ImVec2 Survive::Centroid::getCenter(const b2Vec2 &localCenter, const Survive::Camera &camera, const glm::vec3 &position,
									const glm::mat4 &modelMatrix, float x, float y, float width, float height)
{
	float scale = Constants::BOX2D_SCALE;
	glm::vec2 center{localCenter.x / scale, localCenter.y / scale};

	glm::vec2 point{center.x + position.x, center.y + position.y};

	return Util::getScreenPos(camera, modelMatrix, point, x, y, width, height);
}

