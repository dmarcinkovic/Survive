//
// Created by david on 07. 03. 2021..
//

#ifndef SURVIVE_LOG_H
#define SURVIVE_LOG_H

#include <imgui.h>

struct LogInfo
{
	const char *message;
	const char *title;

	float width, height;

	bool open;
	double time;
};

class Log
{
private:
	static LogInfo m_LogInfo;

public:
	static void
	logWindow(const char *title, const char *message, const ImVec2 &size = ImVec2(300, 100), double time = 3.0);

private:
	static void drawLogWindow();

	friend class Editor;
};


#endif //SURVIVE_LOG_H
