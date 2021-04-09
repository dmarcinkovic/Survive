//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "../../engine/display/Display.h"
#include "../../engine/texture/Texture.h"
#include "../../engine/renderer/Loader.h"


LogInfo Log::m_LogInfo;

void Log::logWindow(const char *message, const ImVec2 &size, double time)
{
	m_LogInfo.message = message;

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

	if (m_LogInfo.open)
	{
		m_LogInfo.time -= Display::getFrameTime();
		if (m_LogInfo.time <= 0)
		{
			m_LogInfo.open = false;
			return;
		}

		auto[width, height] = Display::getWindowSize<float>();
		ImGui::Begin("", &m_LogInfo.open, flags);

		static GLuint icon = Loader::loadTexture("res/error.png");
		auto image = reinterpret_cast<void *>(icon);

		ImVec2 imageSize(m_LogInfo.height / 2.0f, m_LogInfo.height / 2.0f);
		ImGui::Image(image, imageSize);

		ImGui::SameLine();
		ImGui::SetWindowFontScale(1.2f);
		ImGui::TextWrapped("%s", m_LogInfo.message);

		ImGui::SetWindowPos(ImVec2(width - m_LogInfo.width, height - m_LogInfo.height));
		ImGui::SetWindowSize(ImVec2(m_LogInfo.width, m_LogInfo.height));

		ImGui::End();
	}
}

void Log::drawIcon(const LogInfo &logInfo, GLuint warnIcon, GLuint errorIcon, GLuint infoIcon)
{
	ImVec2 imageSize(logInfo.height / 2.0f, logInfo.height / 2.0f);
	ImTextureID icon = nullptr;

	switch (logInfo.logType)
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

	ImGui::Image(icon, imageSize);
}
