//
// Created by david on 18. 08. 2021..
//

#include "ContentBrowser.h"
#include "Log.h"

Survive::ContentBrowser::ContentBrowser()
		: m_DirectoryContent(FileUtil::listCurrentDirectory()), m_Uv0(0, 1), m_Uv1(1, 0),
		  m_CurrentDirectory(std::filesystem::current_path()),
		  m_Tree(m_CurrentDirectory, m_DirectoryContent)
{
	m_Icons = m_Loader.loadAllTextures(
			{"assets/textures/grey_folder.png", "assets/textures/txt_file.png", "assets/textures/cpp_icon.png",
			 "assets/textures/readme_icon.png", "assets/textures/image_icon.png", "assets/textures/obj_icon.png",
			 "assets/textures/unknown_icon.png", "assets/textures/survive_icon.png", "assets/textures/dae_icon.png"});

	m_Lupa = m_Loader.loadTexture("assets/textures/lupa.png");

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
	}

	ImGui::End();

	ImGui::PopStyleColor(3);
}

void Survive::ContentBrowser::setColors()
{
	ImVec4 windowBg = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, windowBg);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.02f, 0.02f, 0.02f, 1));
}

ImTextureID Survive::ContentBrowser::getIcon(const std::filesystem::path &file)
{
	m_ImageIndex = UNKNOWN;
	if (std::filesystem::is_directory(file))
	{
		m_ImageIndex = FOLDER;
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
		} else if (extension == ".survive")
		{
			m_ImageIndex = SURVIVE;
		} else if (extension == ".dae")
		{
			m_ImageIndex = DAE;
		}
	}

	return reinterpret_cast<ImTextureID>(m_Icons[m_ImageIndex].textureId());
}

void Survive::ContentBrowser::drawIcon(ImTextureID image, const std::filesystem::path &file)
{
	static ImVec2 size(ICON_SIZE, ICON_SIZE);
	std::string filename = file.filename().string();

	ImGui::PushID(file.c_str());
	ImGui::ImageButton(image, size, m_Uv0, m_Uv1);
	ImGui::PopID();

	iconDoubleClicked(file);
	startDraggingIcon(file);

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

		try
		{
			ImTextureID image = getIcon(file.path);

			ImGui::BeginGroup();

			float availableRegion = ImGui::GetContentRegionAvail().x;

			drawIcon(image, file.path);
			ImGui::EndGroup();

			alignIcons(availableRegion);
		} catch (const std::filesystem::filesystem_error &ignorable)
		{
		}
	}

	ImGui::EndChild();
}

void Survive::ContentBrowser::renderImageWindow()
{
	static const ImVec2 imageSize(300, 300);

	if (m_DrawImage)
	{
		std::string windowTitle = m_ImageFilename + "###Image view";
		if (ImGui::Begin(windowTitle.c_str(), &m_DrawImage))
		{
			auto image = reinterpret_cast<ImTextureID>(m_Image.textureId());

			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 imagePosition((windowSize.x - imageSize.x) / 2.0f, (windowSize.y - imageSize.y) / 2.0f);

			ImGui::SetCursorPos(imagePosition);
			ImGui::Image(image, imageSize, m_Uv0, m_Uv1);
		}

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
	m_InputText = ImGui::IsItemFocused();

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

const std::filesystem::path &Survive::ContentBrowser::getDraggedFile() const
{
	return m_DraggedFile;
}

bool Survive::ContentBrowser::isUsingKeyEvents() const
{
	return m_InputText;
}

void Survive::ContentBrowser::startDraggingIcon(const std::filesystem::path &file)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
	{
		m_StartedDragging = true;
		m_DraggedFile = file;
		ImGui::EndDragDropSource();
	}
}

void Survive::ContentBrowser::iconDoubleClicked(const std::filesystem::path &file)
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		if (m_ImageIndex == IMAGE)
		{
			m_DrawImage = true;

			std::string textureName = file.string();

			try
			{
				m_Image = m_Loader.loadTexture(textureName.c_str());
				m_ImageFilename = file.filename().string();
			} catch (const std::exception &exception)
			{
				Log::logMessage(LogType::ERROR, "Cannot load texture " + textureName);
			}
		} else if (m_ImageIndex == FOLDER)
		{
			m_Tree.setCurrentDirectory(file);
			m_ContentChanged = true;
		}
	}
}
