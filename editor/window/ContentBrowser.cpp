//
// Created by david on 18. 08. 2021..
//

#include "ContentBrowser.h"
#include "Loader.h"

Survive::ContentBrowser::ContentBrowser()
		: m_DirectoryContent(FileUtil::listCurrentDirectory()),
		  m_DirectoryIcon(Loader::loadTexture("res/grey_folder.png")),
		  m_Uv0(0, 1), m_Uv1(1, 0)
{
}

void Survive::ContentBrowser::draw()
{
	if (ImGui::Begin("Content browser"))
	{
		for (const File &file : m_DirectoryContent)
		{
			auto image = reinterpret_cast<void *>(m_DirectoryIcon.textureId());

			ImGui::BeginGroup();

			ImGui::Image(image, ImVec2(ICON_SIZE, ICON_SIZE), m_Uv0, m_Uv1);
			ImGui::Text("%s", file.name.c_str());
			ImGui::EndGroup();

			ImGui::SameLine(0.0f, 40);
		}

		ImGui::End();
	}
}
