//
// Created by david on 09. 05. 2021..
//

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

#include "Log.h"
#include "EditorUtil.h"

ImVec4 Survive::EditorUtil::add(const ImVec4 &vec1, const ImVec4 &vec2)
{
	return {vec1.x + vec2.x, vec1.y + vec2.y,
			vec1.z + vec2.z, vec1.w + vec2.w};
}

void
Survive::EditorUtil::loadTexture(OpenDialog &fileChooser, Loader &loader, Texture &texture, std::string &textureName,
								 const char *format, const char *label, bool &changed, bool &open)
{
	showLoadedFile(format, textureName, label, open);

	if (open)
	{
		fileChooser.open(600.0f, 400.0f, &open);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!open && !selectedFilename.empty())
		{
			std::string selectedFile = fileChooser.getSelectedFile().string();

			try
			{
				texture = loader.loadTexture(selectedFile.c_str());

				textureName = selectedFilename;
				changed = true;
			} catch (const std::exception &exception)
			{
				Log::logMessage(LogType::Error, "Could not load texture " + selectedFile);
			}
		}
	}
}

void Survive::EditorUtil::showLoadedFile(const char *format, const std::string &name, const char *label, bool &load)
{
	ImGui::Text(format, name.c_str());
	ImGui::NextColumn();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.45f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.25f, 1.0f));

	if (ImGui::Button(label, ImVec2(150, ImGui::GetTextLineHeight() * 2.0f)))
	{
		load = true;
	}

	ImGui::PopStyleColor(3);
}

void Survive::EditorUtil::drawColumnInputInt(const char *text, const char *label, int &value)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	ImGui::InputInt(label, &value);
	ImGui::NextColumn();
}

void Survive::EditorUtil::drawColumnInputBool(const char *text, const char *label, bool &value)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::Checkbox(label, &value);
	ImGui::NextColumn();
}

bool Survive::EditorUtil::drawColumnInputFloat(const char *text, const char *label, float &value, float minValue, float maxValue)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	bool result;
	if ((result = ImGui::InputFloat(label, &value)))
	{
		value = std::min(maxValue, std::max(minValue, value));
	}

	ImGui::NextColumn();

	return result;
}

bool Survive::EditorUtil::drawColumnDragFloat(const char *text, const char *label,
											  float &value, float minValue, float maxValue, float step)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	bool result;
	if ((result = ImGui::DragFloat(label, &value, step, minValue, maxValue)))
	{
		value = std::min(maxValue, std::max(minValue, value));
	}

	ImGui::NextColumn();

	return result;
}

bool Survive::EditorUtil::drawColumnDragFloat2(const char *text, const char *label, b2Vec2 &value)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	glm::vec2 vec(value.x, value.y);
	bool result;
	if ((result = ImGui::DragFloat2(label, glm::value_ptr(vec))))
	{
		value.x = vec.x;
		value.y = vec.y;
	}

	ImGui::NextColumn();

	return result;
}

void Survive::EditorUtil::drawColumnInputText(const char *label, const char *text, std::string &buffer,
											  ImGuiInputTextFlags flags)
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{0.15f, 0.15f, 0.15f, 0.8f});

	ImGui::TextUnformatted(text);
	ImGui::NextColumn();
	ImGui::SetNextItemWidth(-1.0f);

	ImGui::InputText(label, buffer.data(), buffer.capacity(), flags);

	ImGui::PopStyleColor();
}

bool Survive::EditorUtil::disableButton(bool condition)
{
	bool disabled = false;

	if (condition)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

		disabled = true;
	}

	return disabled;
}

void Survive::EditorUtil::enableButton(bool condition)
{
	if (condition)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
}

void Survive::EditorUtil::drawColumnColorEdit3(const char *text, const char *label, glm::vec3 &color)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1);
	ImGui::ColorEdit3(label, glm::value_ptr(color));
	ImGui::NextColumn();
}

bool Survive::EditorUtil::drawColumnDragFloat3(const char *text, const char *label, rp3d::Vector3 &value, float speed,
											   float minValue, float maxValue)
{
	glm::vec3 vec{value.x, value.y, value.z};

	bool result{};
	if (drawColumnDragFloat3(text, label, vec, speed, minValue, maxValue))
	{
		value.x = vec.x;
		value.y = vec.y;
		value.z = vec.z;

		result = true;
	}

	return result;
}

int Survive::EditorUtil::drawDeleteButton(int index, const Texture &deleteButton, const char *tooltipText)
{
	static const ImVec2 uv0(0, 1);
	static const ImVec2 uv1(1, 0);

	int itemToDelete = -1;
	auto icon = reinterpret_cast<ImTextureID>(deleteButton.textureId());

	ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

	float buttonSize = 1.4f * ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(icon, ImVec2(buttonSize, buttonSize), uv0, uv1))
	{
		itemToDelete = index;
	}

	drawTooltip(tooltipText);

	ImGui::PopStyleColor();
	ImGui::NextColumn();

	return itemToDelete;
}

void Survive::EditorUtil::drawTooltip(const char *text)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(text);
		ImGui::EndTooltip();
	}
}

bool Survive::EditorUtil::drawColumnDragFloat3(const char *text, const char *label, glm::vec3 &value, float speed,
											   float minValue, float maxValue)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();
	ImGui::SetNextItemWidth(-1);

	bool result = ImGui::DragFloat3(label, glm::value_ptr(value), speed, minValue, maxValue);

	ImGui::NextColumn();

	return result;
}
