//
// Created by david on 17. 07. 2021..
//

#ifndef SURVIVE_SKYBOXWINDOW_H
#define SURVIVE_SKYBOXWINDOW_H

#include "FileChooser.h"
#include "Texture.h"

namespace Survive
{
	class SkyboxWindow
	{
	private:
		FileChooser m_FileChooser;
		Texture m_Left;
		std::string m_LeftTextureName;

		bool m_Changed = true;

	public:
		void draw(bool &open, const ImVec2 &windowSize);
	};
}

#endif //SURVIVE_SKYBOXWINDOW_H
