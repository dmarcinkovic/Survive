//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "../../engine/display/Display.h"


LogInfo Log::m_LogInfo;

void Log::logWindow(const char *title, const char *message, const ImVec2 &size, double time)
{
	m_LogInfo.title = title;
	m_LogInfo.message = message;

	m_LogInfo.width = size.x;
	m_LogInfo.height = size.y;

	m_LogInfo.open = true;
	m_LogInfo.time = time;
}

void Log::drawLogWindow()
{
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_NoFocusOnAppearing;

	if (m_LogInfo.open)
	{
		m_LogInfo.time -= Display::getFrameTime();
		if (m_LogInfo.time <= 0)
		{
			m_LogInfo.open = false;
			return;
		}

		auto[width, height] = Display::getWindowSize<int>();
		ImGui::Begin(m_LogInfo.title, &m_LogInfo.open, flags);

		ImGui::TextWrapped("%s", m_LogInfo.message);

		ImGui::SetWindowPos(ImVec2(width - m_LogInfo.width, height - m_LogInfo.height));
		ImGui::SetWindowSize(ImVec2(m_LogInfo.width, m_LogInfo.height));

		ImGui::End();
	}
}
