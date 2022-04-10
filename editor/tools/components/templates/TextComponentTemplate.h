//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_TEXTCOMPONENTTEMPLATE_H
#define SURVIVE_TEXTCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<TextComponent>
	{
	private:
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		bool m_IsUsingKeyEvents{};

		bool m_LoadFont{};
		bool m_LoadTextureAtlas{};

		int m_SelectedItem = -1;
		std::vector<Font> m_Fonts;

		std::vector<const char *> m_Items;
		std::vector<std::pair<const char *, const char *>> m_FontInfo;

		Texture m_FontIcon;
		Texture m_TextureIcon;

	public:
		ComponentTemplate<TextComponent>()
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
		}

		void drawComponent(TextComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Text", visible))
			{
				ImGui::Text("Text");
				Text &text = component.text;

				m_IsUsingKeyEvents = drawTextInput(text, text.m_Text);
				chooseFont(component, text.m_Font);

				chooseFontSpacing(text.m_LineSpacing, text);

				if (ImGui::Checkbox("Center string", &text.m_Centered) &&
					!text.m_Text.empty() && text.m_Font.isFontLoaded())
				{
					text.loadTexture(m_Loader);
				}

				ImGui::Columns();

				drawBorderProperties(text.m_AddBorder, text.m_BorderWidth, text.m_BorderColor);
			}
		}

		[[nodiscard]] bool isUsingKeyEvents() const
		{
			return m_IsUsingKeyEvents;
		}

	private:
		bool drawTextInput(Text &text, std::string &string)
		{
			static const size_t BUFFER_SIZE = 512;

			char *buffer = string.data();

			ImVec2 size(-1, 3 * ImGui::GetTextLineHeight());

			if (ImGui::InputTextMultiline("##Text multiline", buffer, BUFFER_SIZE, size))
			{
				text.setText(buffer, m_Loader);
			}

			bool isItemFocused = ImGui::IsItemFocused();
			ImGui::Separator();

			return isItemFocused;
		}

		void chooseFont(TextComponent &textComponent, Font &font)
		{
			Text &text = textComponent.text;

			drawTextHeader();
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

			drawFontButtons(textComponent, font, text);
			ImGui::EndGroup();
		}

		static void drawTextHeader()
		{
			ImGui::Bullet();
			ImGui::Text("Character");

			ImGui::Text("Font");
			ImGui::SameLine();
		}

		void drawFontButtons(TextComponent &textComponent, Font &font, Text &text)
		{
			loadFontButton(m_FontIcon, "Load font", m_LoadFont);
			loadFont(font, textComponent.fontFile);

			ImGui::SameLine();

			loadFontButton(m_TextureIcon, "Load font texture atlas", m_LoadTextureAtlas);
			loadFontTextureAtlas(text, font, textComponent.textureAtlas);
		}

		void chooseFontSpacing(float &spacing, Text &text)
		{
			ImGui::Columns(2, nullptr, false);

			if (EditorUtil::drawColumnInputFloat("Line Spacing", "##Line spacing", spacing, 0))
			{
				text.loadTexture(m_Loader);
			}

			ImGui::Columns();
			ImGui::Separator();

			ImGui::Columns(2, nullptr, false);
			ImGui::Text("Alignment");

			ImGui::NextColumn();
		}

		static void drawBorderProperties(bool &addBorder, float &borderWidth, glm::vec3 &borderColor)
		{
			ImGui::Separator();
			ImGui::Text("Border");
			ImGui::Indent();

			ImGui::Columns(2, nullptr, false);

			EditorUtil::drawColumnInputBool("Add border", "##Add string border", addBorder);
			EditorUtil::drawColumnInputFloat("Border width", "##Text Border width", borderWidth, 0, 1);
			EditorUtil::drawColumnColorEdit3("Border color", "##Border color", borderColor);

			ImGui::Columns();

			ImGui::Unindent();
			ImGui::NewLine();
		}

		static void loadFontButton(const Texture &icon, const char *text, bool &open)
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
				drawTooltip(text);
			}
		}

		static void drawTooltip(const char *text)
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted(text);
			ImGui::EndTooltip();
		}

		void loadFont(Font &font, std::string &file)
		{
			if (m_LoadFont)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_LoadFont);

				std::filesystem::path selectedFile = m_OpenDialog.getSelectedFile();
				if (!m_LoadFont && !selectedFile.string().empty() && selectedFile.has_extension())
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
							std::string message =
									"Cannot load file with extension: " + selectedFile.extension().string();
							Log::logMessage(LogType::ERROR, message);
						}
					} catch (const std::exception &ignorable)
					{
						Log::logMessage(LogType::ERROR, "Cannot load file: " + selectedFile.string());
					}
				}
			}
		}

		void loadFontTextureAtlas(Text &text, Font &font, std::string &file)
		{
			if (m_LoadTextureAtlas)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_LoadTextureAtlas);

				std::filesystem::path selectedFile = m_OpenDialog.getSelectedFile();
				if (!m_LoadTextureAtlas && !selectedFile.string().empty())
				{
					try
					{
						std::string textureName = selectedFile.string();

						font.setTexture(m_Loader.loadTexture(textureName.c_str()));
						text.loadTexture(m_Loader);
						file = textureName;
					} catch (const std::exception &ignorable)
					{
						Log::logMessage(LogType::ERROR, "Cannot load " + selectedFile.filename().string());
					}
				}
			}
		}
	};
}

#endif //SURVIVE_TEXTCOMPONENTTEMPLATE_H
