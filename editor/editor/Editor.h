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
	static float m_ViewportWidth;
	static float m_ViewportHeight;
	static float m_SceneWindowX;
	static float m_SceneWindowY;

	ImGuiIO &m_Io;
	GLuint m_Scene;
	ImVec4 m_ClearColor;
	ImVec2 m_SceneSize;

	bool m_ShowDemoWindow = true;
	bool m_ShowAnotherWindow = false;

	FileChooser m_FileChooser;
	bool m_OpenDialog = false;

	bool m_IsSceneWindowFocused = true;

public:
	explicit Editor(GLuint scene);

	void render();

	static void dock();

	static void newFrame();

	bool &isSceneWindowFocused();

	static std::pair<float, float> getSceneWindowSize();

	static std::pair<float, float> getSceneWindowPos();

private:
	void renderSceneWindow();

	void renderPropertyWindow();

	void renderMenu();

	void renderOpenDialog();

	static void setColorStyle();
};


#endif //SURVIVE_EDITOR_H
