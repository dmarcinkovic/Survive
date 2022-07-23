//
// Created by david on 07. 03. 2021..
//

#include "LogEditor.h"

Survive::LogEditor::LogEditor()
{
	m_ErrorIcon = m_Loader.loadTexture("assets/textures/error.png");
	m_InfoIcon = m_Loader.loadTexture("assets/textures/info.png");
	m_WarnIcon = m_Loader.loadTexture("assets/textures/warn.png");
}

void Survive::LogEditor::drawLogWindow()
{
	ImGuiWindowFlags flags = !m_LogChanged ? ImGuiWindowFlags_None : ImGuiWindowFlags_UnsavedDocument;

	if (ImGui::Begin("Log window", nullptr, flags))
	{
		m_LogChanged = false;

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

		clearLogs();
	}

	ImGui::End();
}

void Survive::LogEditor::drawIcon(LogType logType) const
{
	float height = 1.5f * ImGui::GetTextLineHeight();
	ImTextureID icon = nullptr;

	switch (logType)
	{
		case LogType::Error:
			icon = reinterpret_cast<ImTextureID>(m_ErrorIcon.textureId());
			break;
		case LogType::Warn:
			icon = reinterpret_cast<ImTextureID>(m_WarnIcon.textureId());
			break;
		case LogType::Info:
			icon = reinterpret_cast<ImTextureID>(m_InfoIcon.textureId());
			break;
	}

	ImGui::Image(icon, ImVec2(height, height), ImVec2(0, 1), ImVec2(1, 0));
}

void Survive::LogEditor::clearLogs()
{
	if (ImGui::BeginPopupContextWindow("##LogWindowMenu"))
	{
		if (ImGui::Selectable("Clear All"))
		{
			m_Buffer.clear();
		}

		ImGui::EndPopup();
	}
}
