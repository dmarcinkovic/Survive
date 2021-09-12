//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>

#include "FileChooser.h"
#include "Display.h"
#include "Loader.h"

Survive::FileChooser::FileChooser()
		: m_CurrentDirectory(std::filesystem::current_path()), m_Root(std::filesystem::current_path().root_path()),
		  m_DirectoryContent(FileUtil::listCurrentDirectory())
{
	Texture folder = Loader::loadTexture("res/folder.png");
	m_Icon = reinterpret_cast<ImTextureID>(folder.textureId());
}

void Survive::FileChooser::save(float windowWidth, float windowHeight, bool *open)
{
	constexpr bool openAction = false;
	drawDialogHeader(windowWidth, windowHeight);

	ImGui::OpenPopup("Save");
	if (ImGui::BeginPopupModal("Save", open, ImGuiWindowFlags_NoDocking))
	{
		drawDialogBody(open, windowHeight, openAction);
		drawSaveFilenameTextbox(open);

		if (m_ConfirmWindow.draw(CONFIRM_WIDTH, CONFIRM_HEIGHT, windowWidth, windowHeight))
		{
			*open = false;
			m_OpenedFile = true;
		}

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(7);
}

void Survive::FileChooser::open(float windowWidth, float windowHeight, bool *open)
{
	constexpr bool openAction = true;

	drawDialogHeader(windowWidth, windowHeight);

	ImGui::OpenPopup("Open");
	if (ImGui::BeginPopupModal("Open", open, ImGuiWindowFlags_NoDocking))
	{
		drawDialogBody(open, windowHeight, openAction);
		drawOpenFilenameTextbox(open);

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(7);
}

void Survive::FileChooser::helpMarker(const char *description)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(description);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

std::filesystem::path Survive::FileChooser::getParentPath(const std::string &currentDirectory)
{
	std::filesystem::path path(currentDirectory.c_str());

	return path.parent_path();
}

void Survive::FileChooser::setupDarkStyleColors()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.267f, 0.267f, 0.267f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.11f, 0.11f, 0.11f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.267f, 0.267f, 0.267f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(1.0f, 1.0f, 1.0f, 0.15f));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.337f, 0.5f, 0.76f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.05f, 0.52f, 0.98f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.26f, 0.588f, 0.98f, 1.0f));
}

void Survive::FileChooser::drawNavigationArrows()
{
	drawLeftArrow();
	drawRightArrow();
	drawUpArrow();
}

void Survive::FileChooser::drawLeftArrow()
{
	if (ImGui::ArrowButton("left", ImGuiDir_Left))
	{
		m_Redo.push(m_CurrentDirectory);
		if (!m_Undo.empty())
		{
			m_CurrentDirectory = m_Undo.top();
			m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

			resetSelectedFile();

			m_Undo.pop();
		}
	}
	ImGui::SameLine();
}

void Survive::FileChooser::drawRightArrow()
{
	if (ImGui::ArrowButton("right", ImGuiDir_Right))
	{
		m_Undo.push(m_CurrentDirectory);
		if (!m_Redo.empty())
		{
			m_CurrentDirectory = m_Redo.top();
			m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

			resetSelectedFile();

			m_Redo.pop();
		}
	}
	ImGui::SameLine();
}

void Survive::FileChooser::drawUpArrow()
{
	if (ImGui::ArrowButton("up", ImGuiDir_Up) && m_CurrentDirectory != m_Root)
	{
		m_Redo.push(m_CurrentDirectory);

		m_CurrentDirectory = getParentPath(m_CurrentDirectory);
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();
	}

	ImGui::SameLine();
}

void Survive::FileChooser::drawCheckbox()
{
	ImGui::Checkbox("Hidden", &m_Hidden);

	if (m_Previous != m_Hidden)
	{
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);
		resetSelectedFile();
	}

	m_Previous = m_Hidden;
	ImGui::SameLine();
}

void Survive::FileChooser::drawSaveFilenameTextbox(bool *open)
{
	if (ImGui::BeginChild("save text box"))
	{
		char buffer[BUFFER_SIZE]{};

		m_SelectedFile = -1;
		if (!m_SelectedFileName.empty())
		{
			strcpy(buffer, m_SelectedFileName.c_str());
		}

		ImGui::InputText("", buffer, BUFFER_SIZE);
		m_SelectedFileName = std::string(buffer);

		drawCancelButton(open);
		if (ImGui::Button("Save"))
		{
			savePressed(open);
		}

		ImGui::EndChild();
	}
}

void Survive::FileChooser::drawOpenFilenameTextbox(bool *open)
{
	if (ImGui::BeginChild("open text box"))
	{
		ImGui::InputText("", m_SelectedFileName.data(), BUFFER_SIZE, ImGuiInputTextFlags_ReadOnly);

		drawCancelButton(open);
		if (ImGui::Button("Open"))
		{
			openPressed(open);
		}

		ImGui::EndChild();
	}
}

void Survive::FileChooser::drawTable(float windowHeight, bool *open, bool openAction)
{
	if (ImGui::BeginChild("table_pane", ImVec2{0, windowHeight * 0.7f}))
	{
		if (ImGui::BeginTable("###3ways", 3, tableFlags))
		{
			drawHeader();

			for (int i = 0; i < m_DirectoryContent.size(); ++i)
			{
				File file = m_DirectoryContent[i];
				ImGui::TableNextRow();

				fillTableRow(file, i, open, openAction);
			}
			ImGui::EndTable();
		}
		ImGui::EndChild();
	}
}

void Survive::FileChooser::drawHeader()
{
	ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort);
	ImGui::TableSetupColumn("Size");
	ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_NoSort);

	ImGui::TableSetupScrollFreeze(0, 1);
	ImGui::TableHeadersRow();

	sortDirectoryContent();
}

void Survive::FileChooser::drawCancelButton(bool *open)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.345f, 0.345f, 0.345f, 1.0f));

	ImGui::SameLine();
	if (ImGui::Button("Cancel"))
	{
		*open = false;
	}
	ImGui::SameLine();

	ImGui::PopStyleColor();
}

std::filesystem::path Survive::FileChooser::getSelectedFile() const
{
	if (!m_OpenedFile)
	{
		return std::filesystem::path{};
	}

	std::filesystem::path path(m_CurrentDirectory);
	return path.append(m_SelectedFileName);
}

void Survive::FileChooser::resetSelectedFile()
{
	if (m_DirectoryContent.empty())
	{
		m_SelectedFile = -1;
		m_SelectedFileName = "";
	} else
	{
		m_SelectedFile = 0;
		m_SelectedFileName = m_DirectoryContent[m_SelectedFile].path.filename().string();
	}
}

void Survive::FileChooser::drawIcon()
{
	ImVec2 uv0(0.0f, 1.0f);
	ImVec2 uv1(1.0f, 0.0f);

	ImGui::Image(m_Icon, ImVec2(20, 15), uv0, uv1);
	ImGui::SameLine();
}

void Survive::FileChooser::fillTableRow(const File &file, int index, bool *open, bool openAction)
{
	ImGui::TableNextColumn();
	drawIcon();

	const std::string &filename = file.path.filename().string();

	if (ImGui::Selectable(filename.c_str(), m_SelectedFile == index, ImGuiSelectableFlags_AllowDoubleClick))
	{
		m_SelectedFile = index;
		m_SelectedFileName = filename;
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	{
		if (openAction)
		{
			openPressed(open);
		} else
		{
			savePressed(open);
		}
	}

	ImGui::TableNextColumn();
	if (ImGui::Selectable(FileUtil::getFileSize(file.size, file.type).c_str(), m_SelectedFile == index))
	{
		m_SelectedFile = index;
		m_SelectedFileName = filename;
	}

	ImGui::TableNextColumn();
	if (ImGui::Selectable(FileUtil::getFileType(file.type), m_SelectedFile == index))
	{
		m_SelectedFile = index;
		m_SelectedFileName = filename;
	}
}

void Survive::FileChooser::openPressed(bool *open)
{
	if (directoryChosen())
	{
		buttonDoublePress();
	} else
	{
		*open = false;
		m_OpenedFile = true;
	}
}

bool Survive::FileChooser::sortByFilename(const File &file1, const File &file2)
{
	const std::string &filename1 = file1.path.filename().string();
	const std::string &filename2 = file2.path.filename().string();

	return filename1.compare(filename2) < 0;
}

bool Survive::FileChooser::sortBySize(const File &file1, const File &file2)
{
	return file1.size < file2.size;
}

void Survive::FileChooser::sortDirectoryContent()
{
	if (ImGuiTableSortSpecs *sortSpecs = ImGui::TableGetSortSpecs())
	{
		if (sortSpecs->SpecsDirty)
		{
			std::function<bool(const File &, const File &)> comparator =
					sortSpecs->Specs->ColumnIndex == 0 ? sortByFilename : sortBySize;

			if (sortSpecs->Specs->SortDirection == ImGuiSortDirection_Ascending)
			{
				std::sort(m_DirectoryContent.begin(), m_DirectoryContent.end(), comparator);
			} else
			{
				std::sort(m_DirectoryContent.rbegin(), m_DirectoryContent.rend(), comparator);
			}

			sortSpecs->SpecsDirty = false;
		}
	}
}

std::string Survive::FileChooser::getSelectedFilename() const
{
	if (m_OpenedFile)
	{
		std::filesystem::path selectedFile(getSelectedFile());
		return std::filesystem::relative(selectedFile);
	}

	return "";
}

void Survive::FileChooser::drawDialogHeader(float windowWidth, float windowHeight)
{
	setupDarkStyleColors();

	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{windowWidth, windowHeight}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);
	m_OpenedFile = false;
}

void Survive::FileChooser::drawDialogBody(bool *open, float windowHeight, bool openAction)
{
	drawNavigationArrows();
	ImGui::InputText("", m_CurrentDirectory.data(), 255, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();

	drawCheckbox();
	helpMarker("Show hidden files");

	drawTable(windowHeight, open, openAction);
}

void Survive::FileChooser::savePressed(bool *open)
{
	if (directoryChosen())
	{
		buttonDoublePress();
		return;
	}

	std::filesystem::path path(m_CurrentDirectory);
	std::string file = path.append(m_SelectedFileName);

	if (std::filesystem::exists(file))
	{
		m_ConfirmWindow.openConfirmWindow();
	} else
	{
		*open = false;
		m_OpenedFile = true;
	}
}

void Survive::FileChooser::buttonDoublePress()
{
	std::filesystem::path path(m_CurrentDirectory);

	m_Undo.push(m_CurrentDirectory);
	m_CurrentDirectory = path.append(m_SelectedFileName);
	m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

	resetSelectedFile();
}

bool Survive::FileChooser::directoryChosen() const
{
	return m_SelectedFile >= 0 && m_DirectoryContent[m_SelectedFile].type == std::filesystem::file_type::directory;
}
