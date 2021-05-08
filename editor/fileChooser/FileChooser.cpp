//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <iostream>

#include "FileChooser.h"
#include "Display.h"
#include "Loader.h"

Survive::FileChooser::FileChooser()
		: m_CurrentDirectory(std::filesystem::current_path()), m_Root(std::filesystem::current_path().root_path()),
		  m_DirectoryContent(listCurrentDirectory()), m_SelectedFileName(m_DirectoryContent.front().name)
{
	Texture folder = Loader::loadTexture("res/folder.png");
	m_Icon = reinterpret_cast<ImTextureID>(folder.textureId());
}

void Survive::FileChooser::open(float windowWidth, float windowHeight, bool *open)
{
	setupDarkStyleColors();

	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{windowWidth, windowHeight}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	ImGui::OpenPopup("Open");
	if (ImGui::BeginPopupModal("Open", open, ImGuiWindowFlags_NoDocking))
	{
		drawNavigationArrows();

		ImGui::InputText("", m_CurrentDirectory.data(), 255, ImGuiInputTextFlags_ReadOnly);

		ImGui::SameLine();

		drawCheckbox();

		helpMarker("Show hidden files");

		drawTable(windowHeight, open);
		drawFilenameTextbox(open);

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(4);
}

std::vector<Survive::File> Survive::FileChooser::listDirectory(const std::string &directory, bool showHidden)
{
	std::filesystem::directory_iterator directoryIterator(directory);
	std::vector<File> files;

	for (auto const &path : directoryIterator)
	{
		File file;
		file.name = path.path().filename();

		if (!showHidden && file.name.front() == '.')
		{
			continue;
		}

		if (path.is_regular_file())
		{
			file.size = path.file_size();
		}

		file.type = path.status().type();
		files.emplace_back(file);
	}

	return files;
}

std::vector<Survive::File> Survive::FileChooser::listCurrentDirectory()
{
	auto workingDirectory = std::filesystem::current_path();

	return listDirectory(std::filesystem::absolute(workingDirectory), false);
}

std::string Survive::FileChooser::getFileSize(unsigned long fileSize, std::filesystem::file_type type)
{
	if (type != std::filesystem::file_type::regular)
	{
		return "";
	}

	static const int BYTE = 1024;
	auto size = static_cast<double>(fileSize);

	double kilobytes = size / BYTE;

	if (kilobytes < 1.0)
	{
		return std::to_string(fileSize);
	}

	std::ostringstream stream;

	double megabytes = kilobytes / BYTE;

	if (megabytes < 1.0)
	{
		stream << std::setprecision(3) << kilobytes << "K";
		return stream.str();
	}

	double gigabytes = megabytes / BYTE;

	if (gigabytes < 1.0)
	{
		stream << std::setprecision(3) << megabytes << "M";
		return stream.str();
	}

	double terabytes = gigabytes / BYTE;

	if (terabytes < 1.0)
	{
		stream << std::setprecision(3) << gigabytes << "G";
		return stream.str();
	}

	stream << std::setprecision(3) << terabytes << "T";
	return stream.str();
}

const char *Survive::FileChooser::getFileType(std::filesystem::file_type type)
{
	switch (type)
	{
		case std::filesystem::file_type::directory :
			return "directory";
		case std::filesystem::file_type::none:
			return "none";
		case std::filesystem::file_type::not_found:
			return "not found";
		case std::filesystem::file_type::regular:
			return "regular";
		case std::filesystem::file_type::symlink:
			return "symlink";
		case std::filesystem::file_type::block:
			return "block";
		case std::filesystem::file_type::character:
			return "character";
		case std::filesystem::file_type::fifo:
			return "fifo";
		case std::filesystem::file_type::socket:
			return "socket";
		case std::filesystem::file_type::unknown:
			return "unknown";
		default:
			return "";
	}
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
			m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

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
			m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

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
		m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();
	}

	ImGui::SameLine();
}

void Survive::FileChooser::drawCheckbox()
{
	ImGui::Checkbox("Hidden", &m_Hidden);

	if (m_Previous != m_Hidden)
	{
		m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);
		resetSelectedFile();
	}

	m_Previous = m_Hidden;
	ImGui::SameLine();
}

void Survive::FileChooser::drawFilenameTextbox(bool *open)
{
	if (ImGui::BeginChild("text box"))
	{
		ImGui::InputText("", m_SelectedFileName.data(), 255);

		ImGui::SameLine();
		drawCancelButton(open);

		ImGui::SameLine();
		drawOpenButton(open);

		ImGui::EndChild();
	}
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
				const File &file = m_DirectoryContent[i];
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

	if (ImGui::Button("Cancel"))
	{
		*open = false;
	}

	ImGui::PopStyleColor();
}

void Survive::FileChooser::drawOpenButton(bool *open)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.337f, 0.5f, 0.76f, 1.0f));

	if (ImGui::Button("Open"))
	{
		openPressed(open);
	}

	ImGui::PopStyleColor();
}

std::string Survive::FileChooser::getSelectedFile() const
{
	std::filesystem::path path(m_CurrentDirectory);
	return path.append(m_SelectedFileName);
}

void Survive::FileChooser::resetSelectedFile()
{
	m_SelectedFile = 0;
	m_SelectedFileName = m_DirectoryContent[m_SelectedFile].name;
}

void Survive::FileChooser::drawIcon()
{
	ImVec2 uv0(0.0f, 1.0f);
	ImVec2 uv1(1.0f, 0.0f);

	ImGui::Image(m_Icon, ImVec2(20, 15), uv0, uv1);
	ImGui::SameLine();
}

void Survive::FileChooser::fillTableRow(const File &file, int index, bool *open)
{
	ImGui::TableNextColumn();
	drawIcon();

	if (ImGui::Selectable(file.name.c_str(), m_SelectedFile == index, ImGuiSelectableFlags_AllowDoubleClick))
	{
		m_SelectedFile = index;
		m_SelectedFileName = file.name;
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	{
		openPressed(open);
	}

	ImGui::TableNextColumn();
	if (ImGui::Selectable(getFileSize(file.size, file.type).c_str(), m_SelectedFile == index))
	{
		m_SelectedFile = index;
		m_SelectedFileName = file.name;
	}

	ImGui::TableNextColumn();
	if (ImGui::Selectable(getFileType(file.type), m_SelectedFile == index))
	{
		m_SelectedFile = index;
		m_SelectedFileName = file.name;
	}
}

void Survive::FileChooser::openPressed(bool *open)
{
	if (m_DirectoryContent[m_SelectedFile].type == std::filesystem::file_type::directory)
	{
		std::filesystem::path path(m_CurrentDirectory);

		m_Undo.push(m_CurrentDirectory);
		m_CurrentDirectory = path.append(m_SelectedFileName);
		m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();
	} else
	{
		*open = false;
	}
}

bool Survive::FileChooser::sortByFilename(const File &file1, const File &file2)
{
	return file1.name.compare(file2.name) < 0;
}

bool Survive::FileChooser::sortBySize(const File &file1, const File &file2)
{
	return file1.size < file2.size;
}

void Survive::FileChooser::sortDirectoryContent()
{
	if (ImGuiTableSortSpecs *sorts_specs = ImGui::TableGetSortSpecs())
	{
		if (sorts_specs->SpecsDirty)
		{
			std::function<bool(const File &, const File &)> comparator =
					sorts_specs->Specs->ColumnIndex == 0 ? sortByFilename : sortBySize;

			if (sorts_specs->Specs->SortDirection == ImGuiSortDirection_Ascending)
			{
				std::sort(m_DirectoryContent.begin(), m_DirectoryContent.end(), comparator);
			} else
			{
				std::sort(m_DirectoryContent.rbegin(), m_DirectoryContent.rend(), comparator);
			}

			sorts_specs->SpecsDirty = false;
		}
	}
}
