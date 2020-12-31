//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H


#include <GL/gl.h>
#include <imgui.h>

class Editor
{
private:
	ImGuiIO &m_Io;
	GLuint m_Scene;
	ImVec4 m_ClearColor;

	bool m_ShowDemoWindow = true;
	bool m_ShowAnotherWindow = false;

public:
	explicit Editor(GLuint scene);

	void render();

	static void dock();

	static void newFrame();

private:
	void renderSceneWindow() const;

	void renderPropertyWindow();
};


#endif //SURVIVE_EDITOR_H
