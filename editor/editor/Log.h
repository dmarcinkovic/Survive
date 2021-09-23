//
// Created by david on 07. 03. 2021..
//

#ifndef SURVIVE_LOG_H
#define SURVIVE_LOG_H

#include <string>
#include <imgui.h>

#include "Texture.h"

namespace Survive
{
	enum class LogType
	{
		WARN, INFO, ERROR
	};

	struct LogInfo
	{
		std::string message;
		LogType logType;
	};

	class Log
	{
	private:
		static LogInfo m_LogInfo;

		using GLuint = unsigned;

	public:
		static void
		logWindow(LogType logType, const std::string &message);

	private:
		static void drawLogWindow();

		static void drawIcon(const Texture &warnIcon, const Texture &errorIcon, const Texture &infoIcon);

		friend class Editor;
	};
}


#endif //SURVIVE_LOG_H
