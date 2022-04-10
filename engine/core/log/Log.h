//
// Created by david on 26. 02. 2022..
//

#ifndef SURVIVE_LOG_H
#define SURVIVE_LOG_H

#include <string>
#include <imgui.h>
#include <utility>
#include <vector>

namespace Survive
{
	enum class LogType
	{
		WARN, INFO, ERROR
	};

	struct LogInfo
	{
		std::string message{};
		LogType logType = LogType::ERROR;

		LogInfo() = default;

		LogInfo(std::string message, LogType logType)
			: message(std::move(message)), logType(logType)
		{}
	};

	class Log
	{
	protected:
		static std::vector<LogInfo> m_Buffer;
		static bool m_LogChanged;

	public:
		static void
		logMessage(LogType logType, const std::string &message);
	};
}

#endif //SURVIVE_LOG_H
