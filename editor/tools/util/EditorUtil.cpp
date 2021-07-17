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
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.25f, 0.25f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.3f, 0.3f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
}

void Survive::EditorUtil::resetStyleColors()
{
	ImGui::PopStyleColor(7);
}

void Survive::EditorUtil::drawTransform3DHeader()
{
	drawTransform2DHeader();
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
	return ImVec4(vec1.x + vec2.x, vec1.y + vec2.y,
				  vec1.z + vec2.z, vec1.w + vec2.w);
}

void Survive::EditorUtil::loadModel(FileChooser &fileChooser, Model &model, std::string &modelName, bool &changed)
{
	static bool load{};
	static Loader loader;

	showLoadedFile("Model: %s", modelName, "Load model", load);

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

void Survive::EditorUtil::loadTexture(Survive::FileChooser &fileChooser, Texture &texture, std::string &textureName,
									  const char *format, const char *label, bool &changed)
{
	static bool load{};

	showLoadedFile(format, textureName, label, load);

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

void Survive::EditorUtil::showLoadedFile(const char *format,
										 const std::string &name, const char *label, bool &load)
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

void Survive::EditorUtil::drawTransform2DHeader()
{
	ImGui::NextColumn();
	ImGui::Text("X");
	ImGui::NextColumn();
	ImGui::Text("Y");
	ImGui::NextColumn();
}

bool Survive::EditorUtil::drawSlider(const char *label, const std::string &text, float &value, float start, float end)
{
	ImGui::NewLine();
	centerText(text);

	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.87f, 0.19f, 0.14f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.88f, 0.46f, 0.05f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 16);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 4);

	ImGui::PushItemWidth(-1);
	bool sliderChanged = ImGui::SliderFloat(label, &value, start, end);
	ImGui::PopItemWidth();

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);

	return sliderChanged;
}

void Survive::EditorUtil::centerText(const std::string &text)
{
	auto size = static_cast<float>(text.size());
	float fontSize = ImGui::GetFontSize() * size / 2.0f;
	ImGui::SameLine(ImGui::GetWindowSize().x / 2 - fontSize + (fontSize / 2));
	ImGui::Text("%s", text.c_str());
}

void Survive::EditorUtil::loadQuadModel(bool &changed, Survive::TexturedModel &texturedModel, Survive::Loader &loader)
{
	if (changed && texturedModel.isValidTexture())
	{
		changed = false;

		if (!texturedModel.isValidModel())
		{
			texturedModel.getModel() = loader.renderQuad();
		}
	}
}

void Survive::EditorUtil::toggleButton(const char *stringId, bool *v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(stringId, ImVec2(width, height)))
	{
		*v = !*v;
	}

	ImU32 backgroundColor;
	if (ImGui::IsItemHovered())
	{
		backgroundColor = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) :
						  IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
	} else
	{
		backgroundColor = *v ? IM_COL32(145, 211, 68, 255) :
						  IM_COL32(218, 218, 218, 255);
	}

	drawList->AddRectFilled(p, ImVec2(p.x + width, p.y + height), backgroundColor, height * 0.5f);
	drawList->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f,
							  IM_COL32(255, 255, 255, 255));

}

void Survive::EditorUtil::loadSound(Survive::FileChooser &fileChooser, Survive::AudioMaster &audioMaster, ALint &sound,
									std::string &soundFile, bool &changed)
{
	static bool load{};

	showLoadedFile("Sound: %s", soundFile, "Load sound", load);

	if (load)
	{
		fileChooser.open(600.0f, 400.0f, &load);
		if (!load && !fileChooser.getSelectedFilename().empty())
		{
			std::string selectedFile = fileChooser.getSelectedFile();

			try
			{
				sound = audioMaster.loadSound(selectedFile.c_str());
				soundFile = fileChooser.getSelectedFilename();
				changed = true;
			} catch (const std::exception &ignorable)
			{}
		}
	}
}
