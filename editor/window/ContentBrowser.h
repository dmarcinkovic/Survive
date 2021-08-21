//
// Created by david on 18. 08. 2021..
//

#ifndef SURVIVE_CONTENTBROWSER_H
#define SURVIVE_CONTENTBROWSER_H

#include <imgui.h>
#include <vector>

#include "FileUtil.h"

namespace Survive
{
	class ContentBrowser
	{
	private:
		std::vector<File> m_DirectoryContent;
		

	public:
		ContentBrowser();

		void draw();
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
