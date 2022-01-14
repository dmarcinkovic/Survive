//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "Loader.h"

std::vector<Survive::LogInfo> Survive::Log::m_Buffer;
bool Survive::Log::m_LogViewed = true;

Survive::Log::Log()
{
	m_ErrorIcon = m_Loader.loadTexture("assets/textures/error.png");
	m_InfoIcon = m_Loader.loadTexture("assets/textures/info.png");
	m_WarnIcon = m_Loader.loadTexture("assets/textures/warn.png");
}

void Survive::Log::logWindow(LogType logType, const std::string &message)
{
	m_Buffer.emplace_back(message, logType);
	m_LogViewed = false;
}

void Survive::Log::drawLogWindow()
{
	ImGuiWindowFlags flags = m_LogViewed ? ImGuiWindowFlags_None : ImGuiWindowFlags_UnsavedDocument;

	if (ImGui::Begin("Log window", nullptr, flags))
	{
		m_LogViewed = true;

		auto numberOfItems = static_cast<int>(m_Buffer.size());
		int start = numberOfItems - ITEMS_VISIBLE;

		if (ImGui::BeginTable("###Log table", 1, ImGuiTableFlags_RowBg))
		{
			for (int i = std::max(0, start); i < numberOfItems; ++i)
			{
				ImGui::TableNextColumn();

				drawIcon(m_Buffer[i].logType);
				ImGui::SameLine();
				ImGui::TextUnformatted(m_Buffer[i].message.c_str());
			}

			ImGui::EndTable();
		}
	}

	ImGui::End();
}

void Survive::Log::drawIcon(LogType logType) const
{
	float height = 1.5f * ImGui::GetTextLineHeight();
	ImTextureID icon = nullptr;

	switch (logType)
	{
		case LogType::ERROR:
			icon = reinterpret_cast<ImTextureID>(m_ErrorIcon.textureId());
			break;
		case LogType::WARN:
			icon = reinterpret_cast<ImTextureID>(m_WarnIcon.textureId());
			break;
		case LogType::INFO:
			icon = reinterpret_cast<ImTextureID>(m_InfoIcon.textureId());
			break;
	}

	ImGui::Image(icon, ImVec2(height, height), ImVec2(0, 1), ImVec2(1, 0));
}
