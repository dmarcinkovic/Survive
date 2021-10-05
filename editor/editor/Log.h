//
// Created by david on 07. 03. 2021..
//

#ifndef SURVIVE_LOG_H
#define SURVIVE_LOG_H

#include <string>
#include <imgui.h>
#include <utility>
#include <vector>

#include "Texture.h"

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
	private:
		static constexpr int ITEMS_VISIBLE = 10;

		static std::vector<LogInfo> m_Buffer;

		Texture m_ErrorIcon;
		Texture m_InfoIcon;
		Texture m_WarnIcon;

	public:
		Log();

		static void
		logWindow(LogType logType, const std::string &message);

		void drawLogWindow();

	private:
		void drawIcon(LogType logType) const;
	};
}


#endif //SURVIVE_LOG_H
