//
// Created by david on 07. 03. 2021..
//

#include "Log.h"
#include "Texture.h"
#include "Loader.h"

Survive::LogInfo Survive::Log::m_LogInfo;
std::vector<std::string> Survive::Log::m_Buffer;

void Survive::Log::logWindow(LogType logType, const std::string &message)
{
	m_LogInfo.message = message;
	m_LogInfo.logType = logType;

	m_Buffer.emplace_back(message);
}

void Survive::Log::drawLogWindow()
{
	static Texture errorIcon = Loader::loadTexture("res/error.png");
	static Texture infoIcon = Loader::loadTexture("res/info.png");
	static Texture warnIcon = Loader::loadTexture("res/warn.png");

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13, 0.13, 0.13, 1));

	if (ImGui::Begin("Log window"))
	{
		ImGuiListClipper clipper;

		float itemHeight = ImGui::GetTextLineHeightWithSpacing();
		clipper.Begin(std::numeric_limits<int>::max(), itemHeight);

		while(clipper.Step())
		{
			for (const std::string &line : m_Buffer)
			{
				ImGui::TextUnformatted(line.c_str());
			}
		}

		clipper.End();

//		drawIcon(warnIcon, errorIcon, infoIcon);
//		ImGui::SameLine();
//		ImGui::TextWrapped("%s", m_LogInfo.message.c_str());
	}

	ImGui::End();
	ImGui::PopStyleColor();
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
