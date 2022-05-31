//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_EDITORUTIL_H
#define SURVIVE_EDITORUTIL_H

#include <string>
#include <glm/vec3.hpp>
#include <AL/al.h>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "Renderer.h"
#include "DaeParser.h"
#include "AudioMaster.h"
#include "TexturedModel.h"
#include "OpenDialog.h"
#include "Loader.h"

namespace Survive
{
	class EditorUtil
	{
	public:
		static void loadTexture(OpenDialog &fileChooser, Loader &loader, Texture &texture, std::string &textureName,
								const char *format, const char *label, bool &changed, bool &open);

		static void drawColumnInputInt(const char *text, const char *label, int &value);

		static void drawColumnInputBool(const char *text, const char *label, bool &value);

		static bool drawColumnInputFloat(const char *text, const char *label, float &value,
										 float min = 0, float max = std::numeric_limits<float>::max());

		static bool drawColumnDragFloat(const char *text, const char *label, float &value,
										float min = 0, float max = std::numeric_limits<float>::max(),
										float step = 0.1f);

		static void drawColumnInputText(const char *label, const char *text, std::string &buffer,
										ImGuiInputTextFlags flags = ImGuiInputTextFlags_ReadOnly);

		static bool drawColumnDragFloat2(const char *text, const char *label, b2Vec2 &value);

		static bool drawColumnDragFloat3(const char *text, const char *label, rp3d::Vector3 &value, float speed = 1.0f,
										 float min = 0.0f, float max = 0.0f);

		static bool drawColumnDragFloat3(const char *text, const char *label, glm::vec3 &value, float speed = 1.0f,
										 float min = 0.0f, float max = 0.0f);

		static void drawColumnColorEdit3(const char *text, const char *label, glm::vec3 &color);

		static bool disableButton(bool condition);

		static void enableButton(bool condition);

		static void showLoadedFile(const char *format, const std::string &name, const char *label, bool &load);

		static int drawDeleteButton(int index, const Texture &deleteButton, const char *tooltipText);

	private:
		static ImVec4 add(const ImVec4 &vec1, const ImVec4 &vec2);

		static void drawTooltip(const char *text);
	};
}

#endif //SURVIVE_EDITORUTIL_H
