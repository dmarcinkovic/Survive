//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <iostream>

#include "DaeParser.h"
#include "AudioMaster.h"
#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"
#include "FileChooser.h"
#include "Loader.h"

namespace Survive
{
	class ComponentTemplate
	{
	private:
		AudioMaster m_AudioMaster;
		FileChooser m_FileChooser;
		Loader m_Loader;

		EditorUtil m_EditorUtil;

		int m_SelectedItem = -1;
		Texture m_FontIcon;
		Texture m_TextureIcon;
		std::vector<Font> m_Fonts;

	public:
		ComponentTemplate()
				: m_FontIcon(Loader::loadTexture("res/font_icon.jpg")),
				m_TextureIcon(Loader::loadTexture("res/texture.png"))
		{
			Font arial("res/arial.png");
			arial.loadFontFromFntFile("res/arial.fnt");
			m_Fonts.emplace_back(arial);

			Font candara("res/candara.png");
			candara.loadFontFromFntFile("res/candara.fnt");
			m_Fonts.emplace_back(candara);
		}

		template<typename ComponentType>
		void drawComponent(ComponentType &component, bool * = nullptr)
		{}
	};

	template<>
	inline void ComponentTemplate::drawComponent(Transform3DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Transform3D", visible))
		{
			ImGui::Columns(4);
			EditorUtil::drawTransform3DHeader();

			ImGui::Text("Position");
			EditorUtil::drawTransform3DRow(component.position, "##PosX", "##PosY", "##PosZ");
			ImGui::Text("Rotation");
			EditorUtil::drawTransform3DRow(component.rotation, "##RotX", "##RotY", "##RotZ");
			ImGui::Text("Scale");
			EditorUtil::drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ", 0.0f);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(Render3DComponent &component, bool *visible)
	{
		static bool changed = true;

		if (ImGui::CollapsingHeader("Render3D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::Columns(2);
			m_EditorUtil.loadModel(m_FileChooser, texturedModel.getModel(), component.modelName, changed);
			ImGui::NextColumn();
			m_EditorUtil.loadTexture(m_FileChooser, texturedModel.getTexture(), component.textureName,
									 "Texture: %s", "Load texture", changed);

			if (changed && texturedModel.isValidTexture() && texturedModel.isValidModel())
			{
				changed = false;
			}

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(RigidBodyComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Rigid body", visible))
		{
			ImGui::Checkbox("Transparent", &component.isTransparent);
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(ShadowComponent &component, bool *visible)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.65f, 0.6f, 0.6f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.55f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

		if (ImGui::CollapsingHeader("Shadow", visible))
		{
			ImGui::Checkbox("Add shadow", &component.loadShadow);
		}

		ImGui::PopStyleColor(3);
	}

	template<>
	inline void ComponentTemplate::drawComponent(BloomComponent &component, bool *visible)
	{
		static bool changed = true;

		if (ImGui::CollapsingHeader("Bloom", visible))
		{
			ImGui::Columns(2);
			m_EditorUtil.loadTexture(m_FileChooser, component.emissiveTexture, component.textureName,
									 "Texture: %s", "Load texture", changed);
			ImGui::Columns();

			EditorUtil::drawSlider("##Bloom strength", "Bloom strength", component.bloomStrength, 0.0f, 5.0f);
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(ReflectionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Reflection", visible))
		{
			EditorUtil::drawSlider("##Reflection factor", "Reflection factor", component.reflectionFactor);
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(RefractionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Refraction", visible))
		{
			EditorUtil::drawSlider("##Refraction index", "Refraction index", component.refractiveIndex, 0.0f, 3.0f);
			EditorUtil::drawSlider("##Refraction factor", "Refraction factor", component.refractiveFactor);
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(Render2DComponent &component, bool *visible)
	{
		static bool changed = true;

		if (ImGui::CollapsingHeader("Render2D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::Columns(2);
			m_EditorUtil.loadTexture(m_FileChooser, texturedModel.getTexture(), component.textureName,
									 "Texture: %s", "Load texture", changed);
			EditorUtil::loadQuadModel(changed, texturedModel, m_Loader);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(SoundComponent &component, bool *visible)
	{
		static bool changed = true;

		if (ImGui::CollapsingHeader("Sound", visible))
		{
			if (EditorUtil::drawSlider("##Pitch", "Pitch", component.pitch, 0.0f, 5.0f))
			{
				component.audioSource.setPitch(component.pitch);
			}

			if (EditorUtil::drawSlider("##Gain", "Gain", component.gain, 0.0f, 5.0f))
			{
				component.audioSource.setGain(component.gain);
			}

			EditorUtil::toggleButton("Toggle button", component.playOnLoop);

			ImGui::Columns(2);
			m_EditorUtil.loadSound(m_FileChooser, m_AudioMaster, component.sound, component.soundFile, changed);
			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(SpriteComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Sprite", visible))
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(TextComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Text", visible))
		{
			ImGui::Text("Text");

			std::string &text = component.text.getText();
			char *buffer = text.data();

			float height = ImGui::GetTextLineHeight();
			ImVec2 size(-1, 3 * height);

			if (ImGui::InputTextMultiline("##Text multiline", buffer, text.capacity(), size))
			{
				component.text.setText(buffer, m_Loader);
			}

			std::vector<const char *> items{"Arial", "Candara"};
			ImGui::Separator();
			ImGui::Bullet();
			ImGui::Text("Character");

			ImGui::Text("Font");
			ImGui::SameLine();
			ImGui::BeginGroup();

			if (ImGui::Combo("##Text Font", &m_SelectedItem, items.data(), 2))
			{
				component.text.setFont(m_Fonts[m_SelectedItem]);
				component.text.loadTexture(m_Loader);
			}

			ImGui::SameLine();

			auto fontIcon = reinterpret_cast<ImTextureID>(m_FontIcon.textureId());

			static bool openFont = false;
			if (ImGui::ImageButton(fontIcon, ImVec2(1.5f * height, 1.5f * height), ImVec2(0, 1), ImVec2(1, 0)))
			{
				openFont = true;
			}

			EditorUtil::loadFont(m_FileChooser, component.text.getFont(), openFont);

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Load font");
				ImGui::EndTooltip();
			}

			ImGui::SameLine();

			auto textureIcon = reinterpret_cast<ImTextureID>(m_TextureIcon.textureId());
			static bool openTextureAtlas = false;
			if (ImGui::ImageButton(textureIcon, ImVec2(1.5f * height, 1.5f * height), ImVec2(0, 1), ImVec2(1, 0)))
			{
				openTextureAtlas = true;
			}

			EditorUtil::loadFontTextureAtlas(m_FileChooser, component.text, m_Loader, openTextureAtlas);

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Load font texture atlas");
				ImGui::EndTooltip();
			}

			ImGui::EndGroup();

			ImGui::Columns(2, nullptr, false);
			ImGui::Text("Line Spacing");
			ImGui::NextColumn();

			float v = 0;
			ImGui::SetNextItemWidth(-1);
			ImGui::InputFloat("##Line spacing", &v);

			ImGui::Columns();

			ImGui::Separator();
			ImGui::Columns(2, nullptr, false);
			ImGui::Text("Alignment");

			ImGui::NextColumn();

			bool a{};
			ImGui::Checkbox("Center text", &a);

			ImGui::Columns();

			ImGui::Separator();
			ImGui::Text("Border");
			ImGui::Indent();

			ImGui::Columns(2, nullptr, false);
			ImGui::Text("Add border");
			ImGui::NextColumn();

			bool addBorder{};
			ImGui::Checkbox("##Add text border", &addBorder);
			ImGui::NextColumn();
			ImGui::Text("Border width");
			ImGui::NextColumn();
			float borderWidth{};
			ImGui::SetNextItemWidth(-1);
			ImGui::InputFloat("##Text Border width", &borderWidth);
			ImGui::NextColumn();
			ImGui::Text("Border color");
			ImGui::NextColumn();

			glm::vec3 borderColor{};
			ImGui::SetNextItemWidth(-1);
			ImGui::ColorEdit3("##Border color", glm::value_ptr(borderColor));
			ImGui::Columns();

			ImGui::Unindent();

			ImGui::NewLine();
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
