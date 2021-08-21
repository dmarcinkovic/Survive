//
// Created by david on 18. 08. 2021..
//

#include <filesystem>
#include <iostream>

#include "ContentBrowser.h"

Survive::ContentBrowser::ContentBrowser()
	: m_DirectoryContent(FileUtil::listCurrentDirectory())
{
}

void Survive::ContentBrowser::draw()
{
	if (ImGui::Begin("Content browser"))
	{


		ImGui::End();
	}
}
