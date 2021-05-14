//
// Created by david on 09. 05. 2021..
//

#include <imgui.h>

#include "Log.h"
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
	setDragFloat(vec.y, y, ImVec4(0, 0.4f, 0, 1), ImVec4(0, 0.2f, 0, 1));
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

void Survive::EditorUtil::loadModel(FileChooser &fileChooser, Model &model, bool &changed)
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
		if (!load && !fileChooser.getSelectedFilename().empty())
		{
			std::optional<Model> loadedModel = getLoadedModel(fileChooser, loader);

			if (loadedModel.has_value())
			{
				modelName = fileChooser.getSelectedFilename();
				model = loadedModel.value();
				changed = true;
			}
		}
	}
}

std::optional<Survive::Model>
Survive::EditorUtil::getLoadedModel(const Survive::FileChooser &fileChooser, Loader &loader)
try
{
	std::string selectedFile = fileChooser.getSelectedFile();
	Model model = ObjParser::loadObj(selectedFile.c_str(), loader);

	return model.isValidModel() ? model : std::optional<Survive::Model>{};
} catch (const std::exception &exception)
{
	Log::logWindow(LogType::ERROR, "Error while parsing .obj file");
	return {};
}


void Survive::EditorUtil::loadTexture(Survive::FileChooser &fileChooser, Texture &texture, bool &changed)
{
	static bool load{};
	static std::string textureName;

	ImGui::Text("Texture: %s", textureName.c_str());
	ImGui::NextColumn();
	if (ImGui::Button("Load texture"))
	{
		load = true;
	}

	if (load)
	{
		fileChooser.open(600.0f, 400.0f, &load);
		if (!load && !fileChooser.getSelectedFilename().empty())
		{
			std::optional<Texture> loadedTexture = getLoadedTexture(fileChooser);

			if (loadedTexture.has_value())
			{
				textureName = fileChooser.getSelectedFilename();
				texture = loadedTexture.value();
				changed = true;
			}
		}
	}
}

std::optional<Survive::Texture> Survive::EditorUtil::getLoadedTexture(const Survive::FileChooser &fileChooser)
{
	std::string selectedFile = fileChooser.getSelectedFile();
	Texture texture = Loader::loadTexture(selectedFile.c_str());

	if (texture.isValidTexture())
	{
		return texture;
	}

	return {};
}
