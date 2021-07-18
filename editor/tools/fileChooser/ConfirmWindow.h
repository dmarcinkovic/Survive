//
// Created by david on 12. 07. 2021..
//

#ifndef SURVIVE_CONFIRMWINDOW_H
#define SURVIVE_CONFIRMWINDOW_H

#include <imgui.h>

class ConfirmWindow
{
private:
	bool m_Confirm{};
	bool m_Result{};

public:
	bool draw(float width, float height, float parentWidth, float parentHeight);

	void openConfirmWindow();

private:
	static ImVec2 calcNextWindowPos(const ImVec2 &size, float parentWidth, float parentHeight);

	static void setWindowProperties(float width, float height, float parentWidth, float parentHeight);

	static void setColorStyle();

	static void drawScaledText();

	void drawButtons(float width, float height);

	static void setButtonRedColor();
};


#endif //SURVIVE_CONFIRMWINDOW_H
