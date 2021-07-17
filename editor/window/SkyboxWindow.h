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
		std::vector<Texture> m_Textures;
		std::vector<const char*> m_TextureNames;

		bool m_DialogOpen{};
		uint8_t m_CurrentImage{};

	public:
		SkyboxWindow();

		void draw(bool &open);
	};
}

#endif //SURVIVE_SKYBOXWINDOW_H
