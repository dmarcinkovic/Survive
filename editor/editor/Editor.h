//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H

#include <imgui.h>
#include <utility>

#include "FileChooser.h"
#include "Log.h"

namespace Survive
{
	class Editor
	{
	private:
		ImGuiIO &m_Io;
		GLuint m_Scene;
		ImVec2 m_SceneSize;

		FileChooser m_FileChooser;
		bool m_OpenDialog = false;

		bool m_IsSceneWindowFocused = true;

	public:
		explicit Editor(GLuint scene);

		void render();

		static void dock();

		static void newFrame();

		bool &isSceneWindowFocused();

	private:
		void renderSceneWindow();

		void renderPropertyWindow();

		void renderMenu();

		void renderOpenDialog();

		static void setColorStyle();
	};
}


#endif //SURVIVE_EDITOR_H
