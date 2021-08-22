//
// Created by david on 18. 08. 2021..
//

#ifndef SURVIVE_CONTENTBROWSER_H
#define SURVIVE_CONTENTBROWSER_H

#include <imgui.h>
#include <vector>

#include "FileUtil.h"
#include "Texture.h"

namespace Survive
{
	enum Files
	{
		FOLDER, BINARY, TXT, CPP, README
	};

	class ContentBrowser
	{
	private:
		static constexpr float ICON_SIZE = 70.0f;
		static constexpr float SPACING = 30.0f;
		static constexpr float TEXT_WIDTH = 70.0f;

		const ImVec2 m_Uv0, m_Uv1;
		std::vector<File> m_DirectoryContent{};

		std::vector<Texture> m_Icons;

	public:
		ContentBrowser();

		void draw() const;

	private:
		static void setColors();
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
