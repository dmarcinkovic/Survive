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
	class ContentBrowser
	{
	private:
		static constexpr float ICON_SIZE = 80.0f;
		static constexpr float SPACING = 30.0f;
		static constexpr float TEXT_WIDTH = 80.0f;

		const ImVec2 m_Uv0, m_Uv1;
		std::vector<File> m_DirectoryContent{};

		Texture m_DirectoryIcon;

	public:
		ContentBrowser();

		void draw() const;
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
