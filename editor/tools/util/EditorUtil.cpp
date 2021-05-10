//
// Created by david on 09. 05. 2021..
//

#include <imgui.h>
#include <glm/vec4.hpp>

#include "Loader.h"
#include "ObjParser.h"
#include "EditorUtil.h"

void Survive::EditorUtil::setStyleColors()
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.4f, 0.4f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.6f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
}

void Survive::EditorUtil::drawTransform3DHeader()
{
	ImGui::NextColumn();
	ImGui::Text("X");
	ImGui::NextColumn();
	ImGui::Text("Y");
	ImGui::NextColumn();
	ImGui::Text("Z");
	ImGui::NextColumn();
}

void Survive::EditorUtil::drawTransform3DRow(glm::vec3 &vec, const char *x, const char *y, const char *z)
{
	setDragFloat(vec.x, x, ImVec4(0.5f, 0, 0, 1), ImVec4(0.25f, 0, 0, 1));
	setDragFloat(vec.y, y, ImVec4(0, 0.5f, 0, 1), ImVec4(0, 0.25f, 0, 1));
	setDragFloat(vec.z, z, ImVec4(0, 0, 0.5f, 1), ImVec4(0, 0, 0.25f, 1));

	ImGui::NextColumn();
}

void Survive::EditorUtil::setDragFloat(float &value, const char *label, const ImVec4 &frameBg, const ImVec4 &increment)
{
	ImGui::NextColumn();
	ImGui::PushStyleColor(ImGuiCol_FrameBg, frameBg);

	ImVec4 frameBgHovered = add(frameBg, increment);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, frameBgHovered);

	ImVec4 frameBgActive = add(frameBgHovered, increment);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, frameBgActive);

	ImGui::DragFloat(label, &value);
	ImGui::PopStyleColor(3);
}

ImVec4 Survive::EditorUtil::add(const ImVec4 &vec1, const ImVec4 &vec2)
{
	return ImVec4(vec1.x + vec2.x, vec1.y + vec2.y,
				  vec1.z + vec2.z, vec1.w + vec2.w);
}

std::optional<Survive::Model> Survive::EditorUtil::loadModel(FileChooser &fileChooser)
{
	static bool load{};
	static std::string modelName;
	static Loader loader;

	ImGui::Text("Model: %s", modelName.c_str());
	ImGui::NextColumn();
	if (ImGui::Button("Load model"))
	{
		load = true;
	}

	if (load)
	{
		fileChooser.open(600.0f, 400.0f, &load);
		if (!load)
		{
			std::optional<Model> model = getLoadedModel(fileChooser, loader);
			modelName = model.has_value() ? fileChooser.getSelectedFilename() : "";

			return model;
		}
	}
	return {};
}

std::optional<Survive::Model>
Survive::EditorUtil::getLoadedModel(const Survive::FileChooser &fileChooser, Loader &loader)
try
{
	std::string selectedFile = fileChooser.getSelectedFile();
	return ObjParser::loadObj(selectedFile.c_str(), loader);
} catch (const std::exception &exception)
{
	return {};
}