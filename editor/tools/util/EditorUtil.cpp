//
// Created by david on 09. 05. 2021..
//

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

#include "Log.h"
#include "Loader.h"
#include "ObjParser.h"
#include "Components.h"
#include "Util.h"
#include "EditorUtil.h"

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

void Survive::EditorUtil::drawTransform3DRow(glm::vec3 &vec, const char *x, const char *y,
											 const char *z, float lowerBound)
{
	setDragFloat(vec.x, x, ImVec4(0.5f, 0, 0, 1), ImVec4(0.25f, 0, 0, 1), lowerBound);
	setDragFloat(vec.y, y, ImVec4(0, 0.4f, 0, 1), ImVec4(0, 0.2f, 0, 1), lowerBound);
	setDragFloat(vec.z, z, ImVec4(0, 0, 0.5f, 1), ImVec4(0, 0, 0.25f, 1), lowerBound);

	ImGui::NextColumn();
}

void Survive::EditorUtil::setDragFloat(float &value, const char *label, const ImVec4 &frameBg,
									   const ImVec4 &increment, float lowerBound)
{
	float upperBound = std::numeric_limits<float>::max();

	ImGui::NextColumn();
	ImGui::PushStyleColor(ImGuiCol_FrameBg, frameBg);

	ImVec4 frameBgHovered = add(frameBg, increment);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, frameBgHovered);

	ImVec4 frameBgActive = add(frameBgHovered, increment);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, frameBgActive);

	ImGui::DragFloat(label, &value, 1.0f, lowerBound, upperBound);
	ImGui::PopStyleColor(3);
}

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
				Log::logMessage(LogType::ERROR, "Could not load texture " + selectedFile);
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

void Survive::EditorUtil::loadDraggedModels(entt::registry &registry, Loader &loader, const std::filesystem::path &file,
											const Camera &camera, float x, float y, float width, float height)
try
{
	Model model = ObjParser::loadObj(file.string(), loader);

	if (model.isValidModel())
	{
		auto entity = registry.create();
		registry.emplace<TagComponent>(entity, file.stem().string());

		Render3DComponent renderComponent(TexturedModel(model, Texture()));
		renderComponent.modelName = std::filesystem::relative(file).string();
		registry.emplace<Render3DComponent>(entity, renderComponent);
		registry.emplace<MaterialComponent>(entity, false);

		constexpr float scale = 15.0f;
		glm::vec3 worldSpace = Util::getMouseRay(camera, x, y, width, height) * scale;

		glm::mat4 translate = glm::translate(glm::mat4{1.0f}, camera.position);
		glm::vec3 position = translate * glm::vec4{worldSpace, 1.0f};

		registry.emplace<Transform3DComponent>(entity, position);
	}
} catch (const std::exception &exception)
{
	Log::logMessage(LogType::ERROR, "Error while parsing .obj file");
}

void
Survive::EditorUtil::registerListener(entt::registry &registry, Renderer &renderer, const std::filesystem::path &file,
									  Loader &loader)
{
	std::string filename = file.string();

	renderer.addMousePickingListener([=, &registry, &renderer, &loader](int selectedEntity) {
		if (selectedEntity < 0)
		{
			renderer.popMousePickingListener();
			return;
		}

		try
		{
			Texture texture = loader.loadTexture(filename.c_str());

			auto entity = static_cast<entt::entity>(selectedEntity);

			if (registry.any_of<Render3DComponent>(entity))
			{
				Render3DComponent &renderComponent = registry.get<Render3DComponent>(entity);

				renderComponent.texturedModel.setTexture(texture);
				renderComponent.textureName = std::filesystem::relative(file).string();
			} else if (registry.any_of<Render2DComponent>(entity))
			{
				Render2DComponent &renderComponent = registry.get<Render2DComponent>(entity);

				renderComponent.texturedModel.setTexture(texture);
				renderComponent.textureName = std::filesystem::relative(file).string();
			}
		} catch (const std::exception &exception)
		{
			Log::logMessage(LogType::ERROR, "Cannot load texture " + filename);
		}

		renderer.popMousePickingListener();
	});
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

bool Survive::EditorUtil::drawColumnInputFloat(const char *text, const char *label, float &value, float min, float max)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	bool result;
	if ((result = ImGui::InputFloat(label, &value)))
	{
		value = std::min(max, std::max(min, value));
	}

	ImGui::NextColumn();

	return result;
}

bool Survive::EditorUtil::drawColumnDragFloat(const char *text, const char *label,
											  float &value, float min, float max, float step)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	bool result;
	if ((result = ImGui::DragFloat(label, &value, step, min, max)))
	{
		value = std::min(max, std::max(min, value));
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
