//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H


#include <GL/gl.h>
#include <imgui.h>
#include <utility>
#include "../fileChooser/FileChooser.h"

class Editor
{
private:
	ImGuiIO &m_Io;
	GLuint m_Scene;
	ImVec4 m_ClearColor;
	ImVec2 m_SceneSize;

	bool m_ShowDemoWindow = true;
	bool m_ShowAnotherWindow = false;

	FileChooser m_FileChooser;
	bool m_OpenDialog = false;

	ImGuiStyle *m_Style;

	const ImVec4 &m_WindowBg;
	const ImVec4 m_FrameBg;

public:
	explicit Editor(GLuint scene);

	void render();

	static void dock();

	static void newFrame();

	[[nodiscard]] std::pair<int, int> getSceneWindowSize() const;

private:
	void renderSceneWindow();

	void renderPropertyWindow();

	void renderMenu();

	void renderOpenDialog();

	void setColorStyle();
};


#endif //SURVIVE_EDITOR_H
