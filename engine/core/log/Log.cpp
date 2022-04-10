//
// Created by david on 26. 02. 2022..
//

#include "Log.h"

std::vector<Survive::LogInfo> Survive::Log::m_Buffer;

bool Survive::Log::m_LogChanged = false;

void Survive::Log::logMessage(LogType logType, const std::string &message)
{
	m_Buffer.emplace_back(message, logType);
	m_LogChanged = true;
}
