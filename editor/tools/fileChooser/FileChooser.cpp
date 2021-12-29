//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>

#include "FileChooser.h"
#include "Display.h"
#include "EditorUtil.h"
#include "Log.h"

Survive::FileChooser::FileChooser()
		: m_CurrentDirectory(std::filesystem::current_path()), m_Root(std::filesystem::current_path().root_path()),
		  m_DirectoryContent(FileUtil::listCurrentDirectory())
{
	Texture folder = m_Loader.loadTexture("assets/textures/folder.png");
	m_Icon = reinterpret_cast<ImTextureID>(folder.textureId());
}

void Survive::FileChooser::open(float windowWidth, float windowHeight, bool *open)
{
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
	bool disabled = EditorUtil::disableButton(m_Undo.empty());

	if (ImGui::ArrowButton("left", ImGuiDir_Left))
	{
		m_Redo.push(m_CurrentDirectory);

		m_CurrentDirectory = m_Undo.top();
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();

		m_Undo.pop();
	}

	EditorUtil::enableButton(disabled);
	ImGui::SameLine();
}

void Survive::FileChooser::drawRightArrow()
{
	bool disabled = EditorUtil::disableButton(m_Redo.empty());

	if (ImGui::ArrowButton("right", ImGuiDir_Right))
	{
		m_Undo.push(m_CurrentDirectory);

		m_CurrentDirectory = m_Redo.top();
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();

		m_Redo.pop();
	}

	EditorUtil::enableButton(disabled);
	ImGui::SameLine();
}

void Survive::FileChooser::drawUpArrow()
{
	bool disabled = EditorUtil::disableButton(m_CurrentDirectory == m_Root);

	if (ImGui::ArrowButton("up", ImGuiDir_Up))
	{
		m_Redo.push(m_CurrentDirectory);

		m_CurrentDirectory = m_CurrentDirectory.parent_path();
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory.string(), m_Hidden);

		resetSelectedFile();
	}

	EditorUtil::enableButton(disabled);
	ImGui::SameLine();
}

void Survive::FileChooser::drawCheckbox()
{
	ImGui::Checkbox("Hidden", &m_Hidden);

	if (m_Previous != m_Hidden)
	{
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory.string(), m_Hidden);
		resetSelectedFile();
	}

	m_Previous = m_Hidden;
	ImGui::SameLine();
}

void Survive::FileChooser::drawTable(float windowHeight, bool *open)
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

				fillTableRow(file, i, open);
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

	std::filesystem::path path = m_CurrentDirectory;
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
	static const ImVec2 uv0(0.0f, 1.0f);
	static const ImVec2 uv1(1.0f, 0.0f);

	ImGui::Image(m_Icon, ImVec2(20, 15), uv0, uv1);
	ImGui::SameLine();
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
			auto comparator = sortSpecs->Specs->ColumnIndex == 0 ? sortByFilename : sortBySize;

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
		return std::filesystem::relative(selectedFile).string();
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

void Survive::FileChooser::drawDialogBody(bool *open, float windowHeight)
{
	drawNavigationArrows();

	std::string currentDirectory = m_CurrentDirectory.string();
	ImGui::InputText("##InputText", currentDirectory.data(), 255, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();

	drawCheckbox();
	helpMarker("Show hidden files");

	drawTable(windowHeight, open);
}

void Survive::FileChooser::buttonDoublePress()
{
	std::filesystem::path path = m_CurrentDirectory;
	path.append(m_SelectedFileName);

	try
	{
		m_DirectoryContent = FileUtil::listDirectory(path, m_Hidden);

		m_Undo.push(m_CurrentDirectory);
		m_CurrentDirectory = path;

		resetSelectedFile();
	} catch(const std::filesystem::filesystem_error &error)
	{
		Log::logWindow(LogType::ERROR, "Cannot enter directory: " + m_CurrentDirectory.string());
	}
}

bool Survive::FileChooser::directoryChosen() const
{
	return m_SelectedFile >= 0 && m_DirectoryContent[m_SelectedFile].type == std::filesystem::file_type::directory;
}

void Survive::FileChooser::fillTableRow(const Survive::File &file, int index, bool *open)
{
}
