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
		static constexpr int ICON_SIZE = 70;

		const ImVec2 m_Uv0, m_Uv1;
		std::vector<File> m_DirectoryContent;

		Texture m_DirectoryIcon;

	public:
		ContentBrowser();

		void draw();
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
