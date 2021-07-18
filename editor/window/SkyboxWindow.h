//
// Created by david on 17. 07. 2021..
//

#ifndef SURVIVE_SKYBOXWINDOW_H
#define SURVIVE_SKYBOXWINDOW_H

#include "entt.hpp"
#include "Renderer.h"
#include "FileChooser.h"
#include "Texture.h"

namespace Survive
{
	class SkyboxWindow
	{
	private:
		static constexpr int N = 6;

		FileChooser m_FileChooser;
		std::vector<Texture> m_Textures;
		std::vector<const char*> m_Labels;
		std::vector<std::string> m_TextureNames;

		bool m_DialogOpen{};
		uint8_t m_CurrentImage{};

		bool m_Loaded{};
		entt::entity m_Sky = entt::null;

		Loader m_Loader;
		Model m_Model;

	public:
		SkyboxWindow();

		void draw(entt::registry &registry, Renderer &renderer, bool &open);
	};
}

#endif //SURVIVE_SKYBOXWINDOW_H
