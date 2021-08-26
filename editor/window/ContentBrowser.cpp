//
// Created by david on 18. 08. 2021..
//

#include <iostream>
#include "ContentBrowser.h"
#include "Loader.h"

Survive::ContentBrowser::ContentBrowser()
		: m_CurrentDirectoryContent(FileUtil::listCurrentDirectory()),
		  m_DirectoryContent(m_CurrentDirectoryContent),
		  m_Icons(Loader::loadAllTextures(
				  {"res/grey_folder.png", "res/binary_file.png", "res/txt_file.png", "res/cpp_icon.png",
				   "res/readme_icon.png", "res/image_icon.png", "res/obj_icon.png", "res/unknown_icon.png"})),
		  m_Uv0(0, 1), m_Uv1(1, 0), m_Lupa(Loader::loadTexture("res/lupa.png")),
		  m_CurrentDirectory(std::filesystem::current_path()), m_NestedDirectories(m_CurrentDirectoryContent.size())
{
}

void Survive::ContentBrowser::draw()
{
	setColors();

	renderImageWindow();

	if (ImGui::Begin("Content browser"))
	{
		ImGui::Columns(2);

		if (!m_WidthSet)
		{
			ImGui::SetColumnWidth(0, COLUMN_WIDTH);
			m_WidthSet = true;
		}

		drawDirectoryTree();

		ImGui::NextColumn();
		drawDirectoryContent();

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

ImTextureID Survive::ContentBrowser::getIcon(const std::filesystem::path &file)
{
	m_ImageIndex = UNKNOWN;
	if (std::filesystem::is_directory(file))
	{
		m_ImageIndex = FOLDER;
	} else if (FileUtil::isExecutable(file))
	{
		m_ImageIndex = BINARY;
	} else if (file.has_extension())
	{
		std::string extension = file.extension().string();

		if (extension == ".txt")
		{
			m_ImageIndex = TXT;
		} else if (extension == ".cpp")
		{
			m_ImageIndex = CPP;
		} else if (extension == ".md")
		{
			m_ImageIndex = README;
		} else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
		{
			m_ImageIndex = IMAGE;
		} else if (extension == ".obj")
		{
			m_ImageIndex = OBJ;
		}
	}

	return reinterpret_cast<ImTextureID>(m_Icons[m_ImageIndex].textureId());
}

void Survive::ContentBrowser::drawIcon(ImTextureID image, const std::filesystem::path &file)
{
	static ImVec2 size(ICON_SIZE, ICON_SIZE);
	std::string filename = file.filename().string();

	ImGui::ImageButton(image, size, m_Uv0, m_Uv1);

	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		if (m_ImageIndex == IMAGE)
		{
			m_DrawImage = true;
			m_Image = Loader::loadTexture(file.c_str());
		} else if (m_ImageIndex == FOLDER)
		{
			m_CurrentDirectory = file;
			m_CurrentDirectoryContent = FileUtil::listDirectory(file);
			m_ContentChanged = true;
		}
	}

	ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + TEXT_WIDTH);
	ImGui::TextWrapped("%s", filename.c_str());
	ImGui::PopTextWrapPos();
}

void Survive::ContentBrowser::alignIcons(float availableRegion)
{
	if (availableRegion < 2 * ICON_SIZE + SPACING)
	{
		ImGui::NewLine();
	} else
	{
		ImGui::SameLine(0, SPACING);
	}
}

void Survive::ContentBrowser::drawDirectoryContent()
{
	drawTextDialog();

	if (ImGui::BeginChild("Child2"))
	{
		if (m_ContentChanged)
		{
			m_DirectoryContent = m_CurrentDirectoryContent;
			m_ContentChanged = false;
		}

		for (const File &file: m_DirectoryContent)
		{
			if (!file.path.filename().string().starts_with(m_Buffer))
			{
				continue;
			}

			ImTextureID image = getIcon(file.path);

			ImGui::BeginGroup();

			float availableRegion = ImGui::GetContentRegionAvail().x;

			drawIcon(image, file.path);
			ImGui::EndGroup();

			alignIcons(availableRegion);
		}

		ImGui::EndChild();
	}
}

void Survive::ContentBrowser::drawDirectoryTree()
{
	ImGui::BeginChild("Child1");

	setDirectoryTreeColors();

	drawArrows();
	drawTree();

	ImGui::PopStyleColor(2);
	ImGui::EndChild();
}

void Survive::ContentBrowser::setDirectoryTreeColors()
{
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
}

void Survive::ContentBrowser::drawTree()
{
	ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);

	if (ImGui::TreeNode(m_CurrentDirectory.filename().c_str()))
	{
		for (int i = 0; i < m_CurrentDirectoryContent.size(); ++i)
		{
			const File &file = m_CurrentDirectoryContent[i];
			ImGuiTreeNodeFlags flags = getTreeFlags(file.type);

			if (ImGui::TreeNodeEx(file.path.filename().c_str(), flags))
			{
				if (file.type == std::filesystem::file_type::directory)
				{
					drawNestedDirectories(m_NestedDirectories[i], file);
				}

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

void Survive::ContentBrowser::renderImageWindow()
{
	static const ImVec2 imageSize(300, 300);

	if (m_DrawImage)
	{
		ImGui::Begin("Image view", &m_DrawImage);

		auto image = reinterpret_cast<ImTextureID>(m_Image.textureId());

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 imagePosition((windowSize.x - imageSize.x) / 2.0f, (windowSize.y - imageSize.y) / 2.0f);

		ImGui::SetCursorPos(imagePosition);
		ImGui::Image(image, imageSize, m_Uv0, m_Uv1);

		ImGui::End();
	}
}

void Survive::ContentBrowser::drawNestedDirectories(std::vector<File> &content, const File &file)
{
	if (content.empty())
	{
		content = FileUtil::listDirectory(file.path.string());
	}

	for (const File &nestedFile: content)
	{
		if (ImGui::TreeNodeEx(nestedFile.path.filename().c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}
	}
}

ImGuiTreeNodeFlags Survive::ContentBrowser::getTreeFlags(std::filesystem::file_type type)
{
	if (type == std::filesystem::file_type::directory)
	{
		return ImGuiTreeNodeFlags_None;
	}

	return ImGuiTreeNodeFlags_Leaf;
}

void Survive::ContentBrowser::drawTextDialog()
{
	static const ImVec2 imageSize(25.0f, 25.0f);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.25f, 1.0f));

	auto lupa = reinterpret_cast<ImTextureID>(m_Lupa.textureId());
	ImGui::Image(lupa, imageSize, m_Uv0, m_Uv1);

	ImGui::SameLine();
	ImGui::InputText("##Filter", m_Buffer, BUFFER_SIZE);

	ImGui::PopStyleColor();
}

void Survive::ContentBrowser::drawArrows()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1, 0.2, 0.3, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.1f, 0.2f, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.3f, 0.45f, 1));

	if (ImGui::ArrowButton("Back arrow", ImGuiDir_Left))
	{
		m_RedoStack.push(m_CurrentDirectory);
		m_CurrentDirectory = m_CurrentDirectory.parent_path();
		m_CurrentDirectoryContent = m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory);
	}

	ImGui::SameLine();

	if (ImGui::ArrowButton("Forward arrow", ImGuiDir_Right) && !m_RedoStack.empty())
	{
		m_CurrentDirectory = m_RedoStack.top();
		m_CurrentDirectoryContent = m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory);
		m_RedoStack.pop();
	}

	ImGui::PopStyleColor(3);
}
