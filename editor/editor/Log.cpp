//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "Loader.h"

std::vector<Survive::LogInfo> Survive::Log::m_Buffer;

Survive::Log::Log()
	: m_ErrorIcon(Loader::loadTexture("res/error.png")), m_InfoIcon(Loader::loadTexture("res/info.png")),
		m_WarnIcon(Loader::loadTexture("res/warn.png"))
{
}

void Survive::Log::logWindow(LogType logType, const std::string &message)
{
	m_Buffer.emplace_back(message, logType);
}

void Survive::Log::drawLogWindow()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 1));

	if (ImGui::Begin("Log window"))
	{
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
	ImGui::PopStyleColor();
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
