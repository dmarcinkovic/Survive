//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_UTIL_H
#define SURVIVE_UTIL_H

#include <vector>
#include <string>
#include <regex>
#include <optional>
#include <glm/glm.hpp>
#include <imgui.h>
#include <box2d/box2d.h>

#include "Character.h"
#include "Camera.h"
#include "Transform3DComponent.h"

namespace Survive
{
	class Util
	{
	private:
		static void removeTrailingSpaces(std::string &string);

	public:
		static std::vector<std::string> splitByRegex(const std::string &string);

		static std::vector<std::string> split(std::string string, char delimiter);

		static float getRandom(float first = 0.0f, float second = 1.0f);

		static ImVec2
		getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix, const glm::vec3 &point, float x,
					 float y, float width, float height);

		static ImVec2
		getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix, const glm::vec2 &point, float x,
					 float y, float width, float height);

		static glm::vec3
		getLocalSpace(const Camera &camera, const glm::mat4 &transformationMatrix, const ImVec2 &point, float x,
					  float y, float width, float height);

		static bool mouseHoversPoint(const ImVec2 &point, float radius);

		static bool mouseHoversLine(const ImVec2 &p1, const ImVec2 &p2);

		static float lineDistance(const ImVec2 &p1, const ImVec2 &p2);

		static glm::vec3 getMouseRay(const Camera &camera, float x, float y, float width, float height);
	};
}

#endif //SURVIVE_UTIL_H
