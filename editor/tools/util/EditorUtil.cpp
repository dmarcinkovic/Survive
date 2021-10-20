//
// Created by david on 09. 05. 2021..
//

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Log.h"
#include "Loader.h"
#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"

Survive::EditorUtil::EditorUtil()
		: m_FontIcon(Loader::loadTexture("res/font_icon.jpg")),
		  m_TextureIcon(Loader::loadTexture("res/texture.png")),
		  m_Items{"Arial", "Candara"},
		  m_FontInfo{{"res/arial.png",   "res/arial.fnt"},
					 {"res/candara.png", "res/candara.fnt"}}
{
	Font arial("res/arial.png");
	arial.loadFontFromFntFile("res/arial.fnt");
	m_Fonts.emplace_back(arial);

	Font candara("res/candara.png");
	candara.loadFontFromFntFile("res/candara.fnt");
	m_Fonts.emplace_back(candara);
}

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
	return {vec1.x + vec2.x, vec1.y + vec2.y,
			vec1.z + vec2.z, vec1.w + vec2.w};
}

void Survive::EditorUtil::loadModel(FileChooser &fileChooser, Model &model, std::string &modelName, bool &changed)
{
	showLoadedFile("Model: %s", modelName, "Load model", m_LoadModel);

	if (m_LoadModel)
	{
		fileChooser.open(600.0f, 400.0f, &m_LoadModel);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!m_LoadModel && !selectedFilename.empty())
		{
			std::optional<Model> loadedModel = getLoadedModel(fileChooser);

			if (loadedModel.has_value())
			{
				modelName = selectedFilename;
				model = loadedModel.value();
				changed = true;
			}
		}
	}
}

std::optional<Survive::Model>
Survive::EditorUtil::getLoadedModel(const FileChooser &fileChooser)
try
{
	std::string selectedFile = fileChooser.getSelectedFile().string();
	Model model;

	if (selectedFile.ends_with("obj"))
	{
		model = ObjParser::loadObj(selectedFile, m_Loader);
	} else if (selectedFile.ends_with("dae"))
	{
		model = m_DaeParser.loadDae(selectedFile.c_str(), m_Loader);
	} else
	{
		Log::logWindow(LogType::ERROR, "Unknown file type");
	}

	return model.isValidModel() ? model : std::optional<Survive::Model>{};
} catch (const std::exception &exception)
{
	Log::logWindow(LogType::ERROR, "Error while parsing .obj file");
	return {};
}

void Survive::EditorUtil::loadTexture(FileChooser &fileChooser, Texture &texture, std::string &textureName,
									  const char *format, const char *label, bool &changed)
{
	showLoadedFile(format, textureName, label, m_LoadTexture);

	if (m_LoadTexture)
	{
		fileChooser.open(600.0f, 400.0f, &m_LoadTexture);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!m_LoadTexture && !selectedFilename.empty())
		{
			std::optional<Texture> loadedTexture = getLoadedTexture(fileChooser);

			if (loadedTexture.has_value())
			{
				textureName = selectedFilename;
				texture = loadedTexture.value();
				changed = true;
			}
		}
	}
}

std::optional<Survive::Texture> Survive::EditorUtil::getLoadedTexture(const FileChooser &fileChooser)
{
	std::string selectedFile = fileChooser.getSelectedFile().string();
	Texture texture = Loader::loadTexture(selectedFile.c_str());

	if (texture.isValidTexture())
	{
		return texture;
	}

	return {};
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

	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - fontSize + (fontSize / 2));
	ImGui::Text("%s", text.c_str());
}

void Survive::EditorUtil::loadQuadModel(bool &changed, TexturedModel &texturedModel, Loader &loader)
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

void Survive::EditorUtil::toggleButton(const char *stringId, bool &v)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight() * 1.2f;
	float width = height * 1.55f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(stringId, ImVec2(width, height)))
	{
		v = !v;
	}

	ImU32 backgroundColor;
	if (ImGui::IsItemHovered())
	{
		backgroundColor = v ? IM_COL32(15, 120, 40, 255) : IM_COL32(150, 150, 150, 255);
	} else
	{
		backgroundColor = v ? IM_COL32(51, 244, 92, 255) : IM_COL32(180, 180, 180, 255);
	}

	drawList->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), backgroundColor, height * 0.5f);
	drawList->AddCircleFilled(ImVec2(v ? (pos.x + width - radius) : (pos.x + radius), pos.y + radius),
							  radius - 1.5f, IM_COL32(255, 255, 255, 255));

}

void Survive::EditorUtil::loadSound(FileChooser &fileChooser, AudioMaster &audioMaster, ALint &sound,
									std::string &soundFile, bool &changed)
{
	showLoadedFile("Sound: %s", soundFile, "Load sound", m_LoadSound);

	if (m_LoadSound)
	{
		fileChooser.open(600.0f, 400.0f, &m_LoadSound);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!m_LoadSound && !selectedFilename.empty())
		{
			try
			{
				sound = audioMaster.loadSound(selectedFilename.c_str());
				soundFile = selectedFilename;
				changed = true;
			} catch (const std::exception &ignorable)
			{}
		}
	}
}

void Survive::EditorUtil::loadDraggedModels(entt::registry &registry, const std::filesystem::path &file)
try
{
	Model model = ObjParser::loadObj(file.string(), m_Loader);

	if (model.isValidModel())
	{
		auto entity = registry.create();
		registry.emplace<TagComponent>(entity, file.stem().string());

		Render3DComponent renderComponent(TexturedModel(model, Texture()));
		renderComponent.modelName = std::filesystem::relative(file).string();
		registry.emplace<Render3DComponent>(entity, renderComponent);
	}
} catch (const std::exception &exception)
{
	Log::logWindow(LogType::ERROR, "Error while parsing .obj file");
}

void
Survive::EditorUtil::registerListener(entt::registry &registry, Renderer &renderer, const std::filesystem::path &file)
{
	std::string filename = file.string();

	renderer.addMousePickingListener([=, &registry, &renderer](int selectedEntity) {
		if (selectedEntity < 0)
		{
			renderer.popMousePickingListener();
			return;
		}

		Texture texture = Loader::loadTexture(filename.c_str());
		if (texture.isValidTexture())
		{
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
		}

		renderer.popMousePickingListener();
	});
}

void Survive::EditorUtil::loadFont(FileChooser &fileChooser, Font &font, bool &open, std::string &file)
{
	if (open)
	{
		fileChooser.open(600.0f, 400.0f, &open);

		std::filesystem::path selectedFile = fileChooser.getSelectedFile();
		if (!open && !selectedFile.string().empty() && selectedFile.has_extension())
		{
			try
			{
				if (selectedFile.extension() == ".fnt")
				{
					font.loadFontFromFntFile(selectedFile.string());
					file = selectedFile.string();
				} else if (selectedFile.extension() == ".json")
				{
					font.loadFontFromJsonFile(selectedFile.string());
					file = selectedFile.string();
				} else
				{
					std::string message = "Cannot load file with extension: " + selectedFile.extension().string();
					Log::logWindow(LogType::ERROR, message);
				}
			} catch (const std::exception &ignorable)
			{
				Log::logWindow(LogType::ERROR, "Cannot load file: " + selectedFile.string());
			}
		}
	}
}

void Survive::EditorUtil::loadFontTextureAtlas(FileChooser &fileChooser, Text &text,
											   Font &font, Loader &loader, bool &open, std::string &file)
{
	if (open)
	{
		fileChooser.open(600.0f, 400.0f, &open);

		std::filesystem::path selectedFile = fileChooser.getSelectedFile();
		if (!open && !selectedFile.string().empty())
		{
			try
			{
				std::string textureName = selectedFile.string();

				font.setTexture(Loader::loadTexture(textureName.c_str()));
				text.loadTexture(loader);
				file = textureName;
			} catch (const std::exception &ignorable)
			{
				Log::logWindow(LogType::ERROR, "Cannot load " + selectedFile.filename().string());
			}
		}
	}
}

bool Survive::EditorUtil::drawTextInput(Text &text, std::string &string, Loader &loader)
{
	static const size_t BUFFER_SIZE = 512;

	char *buffer = string.data();
	float height = ImGui::GetTextLineHeight();

	ImVec2 size(-1, 3 * height);

	if (ImGui::InputTextMultiline("##Text multiline", buffer, BUFFER_SIZE, size))
	{
		text.setText(buffer, loader);
	}

	bool isItemFocused = ImGui::IsItemFocused();

	ImGui::Separator();

	return isItemFocused;
}

void Survive::EditorUtil::loadFontButton(const Texture &icon, const char *text, bool &open)
{
	static const ImVec2 uv0(0, 1);
	static const ImVec2 uv1(1, 0);

	auto image = reinterpret_cast<ImTextureID>(icon.textureId());

	float height = ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(image, ImVec2(1.5f * height, 1.5f * height), uv0, uv1))
	{
		open = true;
	}

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(text);
		ImGui::EndTooltip();
	}
}

void Survive::EditorUtil::loadFontBorder(bool &addBorder, float &borderWidth, glm::vec3 &borderColor)
{
	ImGui::Separator();
	ImGui::Text("Border");
	ImGui::Indent();

	ImGui::Columns(2, nullptr, false);
	ImGui::Text("Add border");
	ImGui::NextColumn();

	ImGui::Checkbox("##Add string border", &addBorder);
	ImGui::NextColumn();

	ImGui::Text("Border width");
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1);
	ImGui::InputFloat("##Text Border width", &borderWidth);
	ImGui::NextColumn();

	ImGui::Text("Border color");
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1);
	ImGui::ColorEdit3("##Border color", glm::value_ptr(borderColor));
	ImGui::Columns();

	ImGui::Unindent();

	ImGui::NewLine();
}

void Survive::EditorUtil::chooseFont(FileChooser &fileChooser, TextComponent &textComponent, Font &font)
{
	Text &text = textComponent.text;

	ImGui::Bullet();
	ImGui::Text("Character");

	ImGui::Text("Font");
	ImGui::SameLine();
	ImGui::BeginGroup();

	auto itemsCount = static_cast<int>(m_Items.size());
	if (ImGui::Combo("##Text Font", &m_SelectedItem, m_Items.data(), itemsCount))
	{
		textComponent.textureAtlas = m_FontInfo[m_SelectedItem].first;
		textComponent.fontFile = m_FontInfo[m_SelectedItem].second;

		text.setFont(m_Fonts[m_SelectedItem]);
		text.loadTexture(m_Loader);
	}

	ImGui::SameLine();

	static bool loadFont{};
	EditorUtil::loadFontButton(m_FontIcon, "Load font", loadFont);
	EditorUtil::loadFont(fileChooser, font, loadFont, textComponent.fontFile);

	ImGui::SameLine();

	static bool loadTextureAtlas{};
	EditorUtil::loadFontButton(m_TextureIcon, "Load font texture atlas", loadTextureAtlas);
	EditorUtil::loadFontTextureAtlas(fileChooser, text, font,
									 m_Loader, loadTextureAtlas, textComponent.textureAtlas);
	ImGui::EndGroup();
}

void Survive::EditorUtil::chooseFontSpacing(float &spacing, Text &text, Loader &loader)
{
	ImGui::Columns(2, nullptr, false);
	ImGui::Text("Line Spacing");
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1);
	if (ImGui::InputFloat("##Line spacing", &spacing))
	{
		text.loadTexture(loader);
	}

	ImGui::Columns();

	ImGui::Separator();
	ImGui::Columns(2, nullptr, false);
	ImGui::Text("Alignment");

	ImGui::NextColumn();
}

void Survive::EditorUtil::drawPlayButton(bool &play)
{
	float width = 0.5f * ImGui::GetContentRegionAvailWidth();
	float height = 2.0f * ImGui::GetTextLineHeight();
	ImVec2 size(width, height);

	ImVec2 cursorPos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(cursorPos.x + width / 2.0f, cursorPos.y));

	if (ImGui::Button("Play sound", size))
	{
		play = true;
	}
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

void Survive::EditorUtil::drawColumnInputFloat(const char *text, const char *label, float &value)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	ImGui::InputFloat(label, &value);
	ImGui::NextColumn();
}

bool Survive::EditorUtil::drawColumnDragFloat(const char *text, const char *label,
											  float &value, float min, float max, float step)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	ImGui::SetNextItemWidth(-1.0f);
	bool result = ImGui::DragFloat(label, &value, step, min, max);
	ImGui::NextColumn();

	return result;
}

bool Survive::EditorUtil::drawColumnDragFloat2(const char *text, const char *label, b2Vec2 &value)
{
	ImGui::TextUnformatted(text);
	ImGui::NextColumn();

	glm::vec2 vec(value.x, value.y);
	bool result{};
	if ((result = ImGui::DragFloat2(label, glm::value_ptr(vec))))
	{
		value.x = vec.x;
		value.y = vec.y;
	}

	ImGui::NextColumn();

	return result;
}

void Survive::EditorUtil::drawPolygonPoints(std::vector<b2Vec2> &points, b2PolygonShape &shape)
{
	for (int i = 0; i < points.size(); ++i)
	{
		b2Vec2 &point = points[i];

		const std::string text = "Point" + std::to_string(i + 1);
		const std::string label = "##Polygon p" + std::to_string(i + 1);

		if (drawColumnDragFloat2(text.c_str(), label.c_str(), point))
		{
			shape.Set(points.data(), static_cast<int>(points.size()));
		}
	}
}

void Survive::EditorUtil::addPolygonPoint(std::vector<b2Vec2> &points, b2PolygonShape &shape)
{
	ImGui::TextUnformatted("Add new point");
	ImGui::SameLine();
	if (ImGui::Button(" + "))
	{
		points.emplace_back(0, 0);
		shape.Set(points.data(), static_cast<int>(points.size()));
	}

	ImGui::TextUnformatted("Remove point");
	ImGui::SameLine();
	if (ImGui::Button(" - ") && !points.empty())
	{
		points.pop_back();
		shape.Set(points.data(), static_cast<int>(points.size()));
	}
}
