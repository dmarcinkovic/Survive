//
// Created by david on 18. 08. 2021..
//

#include <iostream>
#include "ContentBrowser.h"
#include "Loader.h"

Survive::ContentBrowser::ContentBrowser()
		: m_DirectoryContent(FileUtil::listCurrentDirectory()),
		  m_Icons(Loader::loadAllTextures(
				  {"res/grey_folder.png", "res/binary_file.png", "res/txt_file.png", "res/cpp_icon.png",
				   "res/readme_icon.png", "res/unknown_icon.png"})),
		  m_Uv0(0, 1), m_Uv1(1, 0),
		  m_CurrentDirectory(std::filesystem::current_path())
{
}

void Survive::ContentBrowser::draw()
{
	setColors();

	if (ImGui::Begin("Content browser"))
	{
		for (const File &file : m_DirectoryContent)
		{
			std::filesystem::path current{m_CurrentDirectory};
			ImTextureID image = getIcon(current.append(file.name));

			ImGui::BeginGroup();

			float availableRegion = ImGui::GetContentRegionAvail().x;

			ImGui::ImageButton(image, ImVec2(ICON_SIZE, ICON_SIZE), m_Uv0, m_Uv1);

			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + TEXT_WIDTH);
			ImGui::TextWrapped("%s", file.name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndGroup();

			if (availableRegion < 2 * ICON_SIZE + SPACING)
			{
				ImGui::NewLine();
			} else
			{
				ImGui::SameLine(0, SPACING);
			}
		}
		ImGui::End();
	}

	ImGui::PopStyleColor(3);
}

void Survive::ContentBrowser::setColors()
{
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.086f, 0.086f, 0.086f, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.02f, 0.02f, 0.02f, 1));
}

ImTextureID Survive::ContentBrowser::getIcon(const std::filesystem::path &file) const
{
	int imageIndex = UNKNOWN;
	if (std::filesystem::is_directory(file))
	{
		imageIndex = FOLDER;
	} else if (FileUtil::isExecutable(file))
	{
		imageIndex = BINARY;
	} else if (file.has_extension())
	{
		std::string extension = file.extension().string();

		if (extension == ".txt")
		{
			imageIndex = TXT;
		} else if (extension == ".cpp")
		{
			imageIndex = CPP;
		} else if (extension == ".md")
		{
			imageIndex = README;
		}
	}

	return reinterpret_cast<ImTextureID>(m_Icons[imageIndex].textureId());
}
