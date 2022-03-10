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

Survive::EditorUtil::EditorUtil()
		: m_Items{"Arial", "Candara"},
		  m_FontInfo{{"assets/fonts/arial.png",   "assets/fonts/arial.fnt"},
					 {"assets/fonts/candara.png", "assets/fonts/candara.fnt"}}
{
	m_FontIcon = m_Loader.loadTexture("assets/textures/font_icon.jpg");
	m_TextureIcon = m_Loader.loadTexture("assets/textures/texture.png");

	Font arial("assets/fonts/arial.png", m_Loader);
	arial.loadFontFromFntFile("assets/fonts/arial.fnt");
	m_Fonts.emplace_back(arial);

	Font candara("assets/fonts/candara.png", m_Loader);
	candara.loadFontFromFntFile("assets/fonts/candara.fnt");
	m_Fonts.emplace_back(candara);

	m_DeleteIcon = m_Loader.loadTexture("assets/textures/delete_icon.png");
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

void
Survive::EditorUtil::loadModel(OpenDialog &fileChooser, Model &model, std::string &modelName, bool &changed, bool &open)
{
	showLoadedFile("Model: %s", modelName, "Load model", open);

	if (open)
	{
		fileChooser.open(600.0f, 400.0f, &open);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!open && !selectedFilename.empty())
		{
			std::optional<Model> loadedModel = getLoadedModel(fileChooser);

			if (loadedModel.has_value())
			{
				modelName = selectedFilename;
				model = Model(loadedModel.value());
				changed = true;
			}
		}
	}
}

std::optional<Survive::Model>
Survive::EditorUtil::getLoadedModel(const OpenDialog &fileChooser)
{
	std::string selectedFile;

	try
	{
		selectedFile = fileChooser.getSelectedFile().string();
		Model model;

		if (selectedFile.ends_with("obj"))
		{
			model = ObjParser::loadObj(selectedFile, m_Loader);
		} else if (selectedFile.ends_with("dae"))
		{
			model = m_DaeParser.loadDae(selectedFile.c_str(), m_Loader);
		} else
		{
			Log::logMessage(LogType::ERROR, "Unknown file type");
		}

		return model.isValidModel() ? model : std::optional<Survive::Model>{};
	} catch (const std::exception &exception)
	{
		Log::logMessage(LogType::ERROR, "Could not load the model from " + selectedFile);
		return {};
	}
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

void Survive::EditorUtil::drawTransform2DHeader()
{
	ImGui::NextColumn();
	ImGui::Text("X");
	ImGui::NextColumn();
	ImGui::Text("Y");
	ImGui::NextColumn();
}

void Survive::EditorUtil::centerText(const std::string &text)
{
	auto size = static_cast<float>(text.size());
	float fontSize = ImGui::GetFontSize() * size / 2.0f;

	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - fontSize + (fontSize / 2));
	ImGui::Text("%s", text.c_str());
}

void Survive::EditorUtil::loadQuadModel(TexturedModel &texturedModel, Loader &loader)
{
	if (!texturedModel.isValidModel())
	{
		texturedModel.getModel() = loader.renderQuad();
	}
}

void Survive::EditorUtil::loadSound(OpenDialog &fileChooser, AudioMaster &audioMaster, ALint &sound,
									std::string &soundFile, bool &changed, bool &open)
{
	showLoadedFile("Sound: %s", soundFile, "Load sound", open);

	if (open)
	{
		fileChooser.open(600.0f, 400.0f, &open);

		std::string selectedFilename = fileChooser.getSelectedFilename();
		if (!open && !selectedFilename.empty())
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

void Survive::EditorUtil::loadDraggedModels(entt::registry &registry, const std::filesystem::path &file,
											const Camera &camera, float x, float y, float width, float height)
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

void Survive::EditorUtil::loadFont(OpenDialog &fileChooser, Font &font, bool &open, std::string &file)
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
					Log::logMessage(LogType::ERROR, message);
				}
			} catch (const std::exception &ignorable)
			{
				Log::logMessage(LogType::ERROR, "Cannot load file: " + selectedFile.string());
			}
		}
	}
}

void Survive::EditorUtil::loadFontTextureAtlas(OpenDialog &fileChooser, Text &text, Font &font,
											   Loader &loader, bool &open, std::string &file)
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

				font.setTexture(loader.loadTexture(textureName.c_str()));
				text.loadTexture(loader);
				file = textureName;
			} catch (const std::exception &ignorable)
			{
				Log::logMessage(LogType::ERROR, "Cannot load " + selectedFile.filename().string());
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

void Survive::EditorUtil::chooseFont(OpenDialog &fileChooser, TextComponent &textComponent, Font &font)
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

void Survive::EditorUtil::drawPolygonPoints(std::vector<b2Vec2> &points, b2PolygonShape &shape) const
{
	int itemToDelete = -1;

	for (int i = 0; i < points.size(); ++i)
	{
		drawPoint(i, points, shape);

		int result;
		if ((result = drawDeleteButton(i, m_DeleteIcon, points, shape)) != -1)
		{
			itemToDelete = result;
		}
	}

	if (itemToDelete != -1)
	{
		points.erase(points.begin() + itemToDelete);
	}
}

void Survive::EditorUtil::addPolygonPoint(std::vector<b2Vec2> &points, b2PolygonShape &shape)
{
	ImGui::TextUnformatted("Add new point");
	ImGui::SameLine();
	if (ImGui::Button(" + ") && points.size() < b2_maxPolygonVertices)
	{
		points.emplace_back(0, 0);
		if (points.size() >= 3)
		{
			shape.Set(points.data(), static_cast<int>(points.size()));
		}
	}

	ImGui::Separator();
}

void Survive::EditorUtil::moveBoxCenter(b2Vec2 *points, const b2Vec2 &diff)
{
	points[0] += diff;
	points[1] += diff;
	points[2] += diff;
	points[3] += diff;
}

void Survive::EditorUtil::drawPoint(int index, std::vector<b2Vec2> &points, b2PolygonShape &shape)
{
	b2Vec2 &point = points[index];

	const std::string text = "Point" + std::to_string(index + 1);
	const std::string label = "##Polygon p" + std::to_string(index + 1);

	ImGui::TextUnformatted(text.c_str());
	ImGui::NextColumn();

	glm::vec2 vec(points[index].x, points[index].y);

	if (ImGui::DragFloat2(label.c_str(), glm::value_ptr(vec)))
	{
		points[index].x = vec.x;
		points[index].y = vec.y;

		if (points.size() >= 3)
		{
			shape.Set(points.data(), static_cast<int>(points.size()));
		}
	}

	ImGui::SameLine();
}

int Survive::EditorUtil::drawDeleteButton(int index, const Texture &deleteIcon, const std::vector<b2Vec2> &points,
										  b2PolygonShape &shape)
{
	static const ImVec2 uv0(0, 1);
	static const ImVec2 uv1(1, 0);

	int itemToDelete = -1;
	ImGui::PushID(index);

	auto icon = reinterpret_cast<ImTextureID>(deleteIcon.textureId());

	ImVec4 windowBgColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
	ImGui::PushStyleColor(ImGuiCol_Button, windowBgColor);

	float buttonSize = 1.4f * ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(icon, ImVec2(buttonSize, buttonSize), uv0, uv1))
	{
		itemToDelete = index;
		if (points.size() >= 3)
		{
			shape.Set(points.data(), static_cast<int>(points.size()));
		}
	}

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted("Delete point");
		ImGui::EndTooltip();
	}

	ImGui::PopStyleColor();

	ImGui::PopID();
	ImGui::NextColumn();

	return itemToDelete;
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

void Survive::EditorUtil::initializeDragDropTarget(entt::entity &connectedBody, std::string &name)
{
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Joint2D"))
		{
			auto *data = reinterpret_cast<std::tuple<int, int, const char *> *>(payload->Data);

			int bodyA = std::get<0>(*data);
			int bodyB = std::get<1>(*data);

			if (bodyA == bodyB)
			{
				Log::logMessage(LogType::ERROR, "Body A should not be equal to body B");
			} else
			{
				connectedBody = static_cast<entt::entity>(bodyB);
				name = std::get<2>(*data);
			}
		}

		ImGui::EndDragDropTarget();
	}
}

void Survive::EditorUtil::drawHingeMotorProperties(HingeJoint2DComponent &component)
{
	static constexpr float min = std::numeric_limits<float>::min();

	b2RevoluteJointDef &jointDef = component.jointDef;

	ImGui::TextUnformatted("Motor");
	ImGui::NextColumn();
	ImGui::NextColumn();

	ImGui::Indent();
	drawColumnInputBool("Use motor", "##UseHingeMotor", jointDef.enableMotor);
	drawColumnDragFloat("Motor speed", "##HingeMotorSpeed", jointDef.motorSpeed, min);
	drawColumnDragFloat("Max motor force", "##HingeMForce", jointDef.maxMotorTorque);
	ImGui::Unindent();
}

void Survive::EditorUtil::drawHingeAngleProperties(Survive::HingeJoint2DComponent &component)
{
	b2RevoluteJointDef &jointDef = component.jointDef;

	ImGui::TextUnformatted("Angle limits");
	ImGui::NextColumn();
	ImGui::NextColumn();

	ImGui::Indent();
	drawColumnInputBool("Use limits", "##UseHingeLimits", jointDef.enableLimit);

	float lowerAngle = glm::degrees(jointDef.lowerAngle);
	if (drawColumnDragFloat("Lower angle", "##HingeLAngle", lowerAngle, -359, 359))
	{
		jointDef.lowerAngle = glm::radians(lowerAngle);
	}

	float upperAngle = glm::degrees(jointDef.upperAngle);
	if (drawColumnDragFloat("Upper angle", "##HingeUAngle", upperAngle, -359, 359))
	{
		jointDef.upperAngle = glm::radians(upperAngle);
	}

	ImGui::Unindent();
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
