//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "../../engine/display/Display.h"
#include "../../engine/texture/Texture.h"
#include "../../engine/renderer/Loader.h"


LogInfo Log::m_LogInfo;

void Log::logWindow(LogType logType, const char *message, const ImVec2 &size, double time)
{
	m_LogInfo.message = message;
	m_LogInfo.logType = logType;

	m_LogInfo.width = size.x;
	m_LogInfo.height = size.y;

	m_LogInfo.open = true;
	m_LogInfo.time = time;
}

void Log::drawLogWindow()
{
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar;

	static GLuint errorIcon = Loader::loadTexture("res/error.png");
	static GLuint infoIcon = Loader::loadTexture("res/info.png");
	static GLuint warnIcon = Loader::loadTexture("res/warn.png");

	if (m_LogInfo.open)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13, 0.13, 0.13, 1));

		m_LogInfo.time -= Display::getFrameTime();
		if (m_LogInfo.time <= 0)
		{
			m_LogInfo.open = false;
			ImGui::PopStyleColor();
			return;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
		auto[width, height] = Display::getWindowSize<float>();
		ImGui::Begin("", &m_LogInfo.open, flags);

		drawIcon(warnIcon, errorIcon, infoIcon);
		ImGui::SameLine();
		ImGui::SetWindowFontScale(1.2f);
		ImGui::TextWrapped("%s", m_LogInfo.message);

		ImGui::SetWindowPos(ImVec2(width - m_LogInfo.width - OFFSET_X, height - m_LogInfo.height - OFFSET_Y));
		ImGui::SetWindowSize(ImVec2(m_LogInfo.width, m_LogInfo.height));

		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
}

void Log::drawIcon(GLuint warnIcon, GLuint errorIcon, GLuint infoIcon)
{
	float height = ImGui::GetTextLineHeight();
	ImTextureID icon = nullptr;

	switch (m_LogInfo.logType)
	{
		case LogType::ERROR:
			icon = reinterpret_cast<ImTextureID>(errorIcon);
			break;
		case LogType::WARN:
			icon = reinterpret_cast<ImTextureID>(warnIcon);
			break;
		case LogType::INFO:
			icon = reinterpret_cast<ImTextureID>(infoIcon);
			break;
	}

	ImGui::Image(icon, ImVec2(height, height), ImVec2(0, 1), ImVec2(1, 0));
}
