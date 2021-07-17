//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "Display.h"
#include "Texture.h"
#include "Loader.h"

Survive::LogInfo Survive::Log::m_LogInfo;

void Survive::Log::logWindow(LogType logType, const std::string& message, const ImVec2 &size, double time)
{
	m_LogInfo.message = message;
	float textWidth = ImGui::CalcTextSize(message.c_str()).x;
	m_LogInfo.logType = logType;

	m_LogInfo.width = std::min(std::max(size.x, textWidth), MAX_WIDTH);
	m_LogInfo.height = size.y;

	m_LogInfo.open = true;
	m_LogInfo.time = time;
}

void Survive::Log::drawLogWindow()
{
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar;

	static Texture errorIcon = Loader::loadTexture("res/error.png");
	static Texture infoIcon = Loader::loadTexture("res/info.png");
	static Texture warnIcon = Loader::loadTexture("res/warn.png");

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
		ImGui::Begin("##Log window", &m_LogInfo.open, flags);

		drawIcon(warnIcon, errorIcon, infoIcon);
		ImGui::SameLine();
		ImGui::TextWrapped("%s", m_LogInfo.message.c_str());

		ImGui::SetWindowPos(ImVec2(width - m_LogInfo.width - OFFSET_X, height - m_LogInfo.height - OFFSET_Y));
		ImGui::SetWindowSize(ImVec2(m_LogInfo.width, m_LogInfo.height));

		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
}

void Survive::Log::drawIcon(const Texture &warnIcon, const Texture &errorIcon, const Texture &infoIcon)
{
	float height = ImGui::GetTextLineHeight();
	ImTextureID icon = nullptr;

	switch (m_LogInfo.logType)
	{
		case LogType::ERROR:
			icon = reinterpret_cast<ImTextureID>(errorIcon.textureId());
			break;
		case LogType::WARN:
			icon = reinterpret_cast<ImTextureID>(warnIcon.textureId());
			break;
		case LogType::INFO:
			icon = reinterpret_cast<ImTextureID>(infoIcon.textureId());
			break;
	}

	ImGui::Image(icon, ImVec2(height, height), ImVec2(0, 1), ImVec2(1, 0));
}
