//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H


#include <GL/gl.h>
#include <imgui.h>
#include <utility>

class Editor
{
private:
	ImGuiIO &m_Io;
	GLuint m_Scene;
	ImVec4 m_ClearColor;
	ImVec2 m_SceneSize;

	bool m_ShowDemoWindow = true;
	bool m_ShowAnotherWindow = false;

public:
	explicit Editor(GLuint scene);

	void render();

	static void dock();

	static void newFrame();

	[[nodiscard]] std::pair<int, int> getSceneWindowSize() const;

private:
	void renderSceneWindow();

	void renderPropertyWindow();

	static void setColorStyle();
};


#endif //SURVIVE_EDITOR_H
