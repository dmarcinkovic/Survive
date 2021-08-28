//
// Created by david on 18. 08. 2021..
//

#include "ContentBrowser.h"
#include "Loader.h"

Survive::ContentBrowser::ContentBrowser()
		: m_DirectoryContent(FileUtil::listCurrentDirectory()),
		  m_Icons(Loader::loadAllTextures(
				  {"res/grey_folder.png", "res/binary_file.png", "res/txt_file.png", "res/cpp_icon.png",
				   "res/readme_icon.png", "res/image_icon.png", "res/obj_icon.png", "res/unknown_icon.png"})),
		  m_Uv0(0, 1), m_Uv1(1, 0), m_Lupa(Loader::loadTexture("res/lupa.png")),
		  m_CurrentDirectory(std::filesystem::current_path()),
		  m_Tree(m_CurrentDirectory, m_DirectoryContent)
{
	m_Tree.addListener([this](auto currentDirectory, auto directoryContent) {
		m_CurrentDirectory = std::move(currentDirectory);
		m_DirectoryContent = std::move(directoryContent);
	});
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

		m_Tree.drawTree();

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
			m_Tree.setCurrentDirectory(file);
			m_ContentChanged = true;
		}
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_StartedDragging = true;
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

	ImGui::BeginChild("Child2");

	if (m_ContentChanged)
	{
		m_DirectoryContent = m_Tree.getDirectoryContent();
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

bool Survive::ContentBrowser::startedDragging() const
{
	return m_StartedDragging;
}

void Survive::ContentBrowser::stopDragging()
{
	m_StartedDragging = false;
}
