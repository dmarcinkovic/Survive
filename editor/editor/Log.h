//
// Created by david on 07. 03. 2021..
//

#ifndef SURVIVE_LOG_H
#define SURVIVE_LOG_H

#include <imgui.h>

enum class LogType
{
	WARN, INFO, ERROR
};

struct LogInfo
{
	const char *message;
	float width, height;
	LogType logType;

	bool open;
	double time;
};

class Log
{
private:
	static LogInfo m_LogInfo;

	using GLuint = unsigned;

public:
	static void
	logWindow(LogType logType, const char *message, const ImVec2 &size = ImVec2(300, 50), double time = 3.0);

private:
	static void drawLogWindow();

	static void drawIcon(GLuint warnIcon, GLuint errorIcon, GLuint infoIcon);

	friend class Editor;
};


#endif //SURVIVE_LOG_H
