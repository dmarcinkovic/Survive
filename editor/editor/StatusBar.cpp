//
// Created by david on 26. 11. 2021..
//

#include <imgui_internal.h>

#include "StatusBar.h"

Survive::StatusBar::StatusBar()
{
	m_PlayButton = m_Loader.loadTexture("assets/textures/play_button.png");
	m_ReloadButton = m_Loader.loadTexture("assets/textures/reload_button.png");
}

void Survive::StatusBar::draw()
{
	ImGuiWindowFlags windowFlags =
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0.6f * ImGui::GetTextLineHeight()));

	setPlayButtonColorStyle();

	float height = ImGui::GetFrameHeightWithSpacing();
	if (ImGui::BeginViewportSideBar("Main side bar", ImGui::GetMainViewport(), ImGuiDir_Up, height, windowFlags))
	{
		drawPlayAndPauseButtons(0.5f * height);

		ImGui::End();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
}

bool Survive::StatusBar::isScenePlaying() const
{
	return m_IsScenePlaying;
}

void Survive::StatusBar::addPlayButtonListener(const Survive::ButtonListener &listener)
{
	m_PlayButtonListeners.emplace_back(listener);
}

void Survive::StatusBar::addReloadButtonListener(const Survive::ButtonListener &listener)
{
	m_ReloadButtonListeners.emplace_back(listener);
}

void Survive::StatusBar::drawPlayAndPauseButtons(float buttonSize)
{
	if (ImGui::BeginMenuBar())
	{
		float width = ImGui::GetContentRegionAvail().x;
		float imagePosX = (width - buttonSize) / 2.0f;
		ImGui::SetCursorPos(ImVec2(imagePosX, 0));

		ImVec2 playButtonSize{buttonSize * 1.2f, buttonSize};
		m_IsScenePlaying = drawImageButton(m_PlayButton, m_IsScenePlaying, playButtonSize, m_PlayButtonListeners,
										   "Play scene");
		ImGui::SameLine();

		ImVec2 reloadButtonSize{buttonSize * 1.2f, buttonSize * 1.2f};
		m_IsScenePlaying = !drawImageButton(m_ReloadButton, !m_IsScenePlaying, reloadButtonSize,
											m_ReloadButtonListeners, "Reload scene");

		ImGui::EndMenuBar();
	}
}

void Survive::StatusBar::setPlayButtonColorStyle()
{
	ImVec4 menuBg = ImGui::GetStyleColorVec4(ImGuiCol_MenuBarBg);

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, menuBg);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.35f, 0.35f, 0.35f, 1));
}

void Survive::StatusBar::notifyListeners(const std::vector<ButtonListener> &listeners)
{
	for (auto const &listener: listeners)
	{
		listener();
	}
}

bool Survive::StatusBar::drawImageButton(const Survive::Texture &image, bool disabled, const ImVec2 &buttonSize,
										 const std::vector<ButtonListener> &buttonListener, const char *tooltipText)
{
	static const ImVec2 uv0(0, 1);
	static const ImVec2 uv1(1, 0);
	auto buttonTexture = reinterpret_cast<ImTextureID>(image.textureId());

	bool popFlag{};
	if (disabled)
	{
		popFlag = true;
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::ImageButton(buttonTexture, buttonSize, uv0, uv1))
	{
		disabled = !disabled;
		notifyListeners(buttonListener);
	}

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(tooltipText);
		ImGui::EndTooltip();
	}

	if (popFlag)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}

	return disabled;
}
