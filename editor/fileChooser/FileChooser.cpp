//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <iostream>

#include "FileChooser.h"
#include "../../engine/display/Display.h"
#include "../../engine/renderer/Loader.h"

FileChooser::FileChooser()
		: m_CurrentDirectory(std::filesystem::current_path()), m_Root(std::filesystem::current_path().root_path()),
		  m_DirectoryContent(listCurrentDirectory()),
		  m_Style(&ImGui::GetStyle()), m_SelectedFileName(m_DirectoryContent.front().name)
{
	GLuint folder = Loader::loadTexture("res/folder.png");
	m_Icon = reinterpret_cast<ImTextureID>(folder);

	setupDarkStyleColors();
}

void FileChooser::open(float windowWidth, float windowHeight, bool *open)
{
	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{windowWidth, windowHeight}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	if (ImGui::Begin("Open", open))
	{
		drawNavigationArrows();

		ImGui::InputText("", m_CurrentDirectory.data(), 255, ImGuiInputTextFlags_ReadOnly);

		ImGui::SameLine();

		drawCheckbox();

		helpMarker("Show hidden files");

		drawHeader();

		drawTable(windowHeight, open);
		drawFilenameTextbox(open);
	}
	ImGui::End();
}

std::vector<File> FileChooser::listDirectory(const std::string &directory, bool showHidden)
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

std::vector<File> FileChooser::listCurrentDirectory(bool showHidden)
{
	auto workingDirectory = std::filesystem::current_path();

	return listDirectory(std::filesystem::absolute(workingDirectory), showHidden);
}

std::string FileChooser::getFileSize(unsigned long fileSize, std::filesystem::file_type type)
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

const char *FileChooser::getFileType(std::filesystem::file_type type)
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
	}
}

void FileChooser::helpMarker(const char *description)
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

std::filesystem::path FileChooser::getParentPath(const std::string &currentDirectory)
{
	std::filesystem::path path(currentDirectory.c_str());

	return path.parent_path();
}

void FileChooser::setupDarkStyleColors()
{
	ImVec4 *colors = m_Style->Colors;

	colors[ImGuiCol_WindowBg] = ImVec4(0.267f, 0.267f, 0.267f, 1.0f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.0f);
}

void FileChooser::drawNavigationArrows()
{
	drawLeftArrow();
	drawRightArrow();
	drawUpArrow();
}

void FileChooser::drawLeftArrow()
{
	if (ImGui::ArrowButton("left", ImGuiDir_Left))
	{
		if (!m_Undo.empty())
		{
			m_Redo.push(m_CurrentDirectory);

			m_CurrentDirectory = m_Undo.top();
			m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

			resetSelectedFile();

			m_Undo.pop();
		}
	}
	ImGui::SameLine();
}

void FileChooser::drawRightArrow()
{
	if (ImGui::ArrowButton("right", ImGuiDir_Right))
	{
		if (!m_Redo.empty())
		{
			m_Undo.push(m_CurrentDirectory);

			m_CurrentDirectory = m_Redo.top();
			m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

			resetSelectedFile();

			m_Redo.pop();
		}
	}
	ImGui::SameLine();
}

void FileChooser::drawUpArrow()
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

void FileChooser::drawCheckbox()
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

void FileChooser::drawFilenameTextbox(bool *open)
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

void FileChooser::drawTable(float windowHeight, bool *open)
{
	if (ImGui::BeginChild("table_pane", ImVec2{0, windowHeight * 0.7f}))
	{
		if (ImGui::BeginTable("###3ways", 3, tableFlags))
		{
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

void FileChooser::drawHeader()
{
	if (ImGui::BeginTable("##3ways", 3, tableFlags))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
		ImGui::TableSetupColumn("Size");
		ImGui::TableSetupColumn("Type");
		ImGui::TableHeadersRow();

		ImGui::EndTable();
	}
}

void FileChooser::drawCancelButton(bool *open)
{
	m_Style->Colors[ImGuiCol_Button] = ImVec4(0.345f, 0.345f, 0.345f, 1.0f);

	if (ImGui::Button("Cancel"))
	{
		*open = false;
	}
}

void FileChooser::drawOpenButton(bool *open)
{
	m_Style->Colors[ImGuiCol_Button] = ImVec4(0.337f, 0.5f, 0.76f, 1.0f);

	if (ImGui::Button("Open"))
	{
		openPressed(open);
	}
}

std::string FileChooser::getSelectedFile() const
{
	std::filesystem::path path(m_CurrentDirectory);
	return path.append(m_SelectedFileName);
}

void FileChooser::resetSelectedFile()
{
	m_SelectedFile = 0;
	m_SelectedFileName = m_DirectoryContent[m_SelectedFile].name;
}

void FileChooser::drawIcon()
{
	ImVec2 uv0(0.0f, 1.0f);
	ImVec2 uv1(1.0f, 0.0f);

	ImGui::Image(m_Icon, ImVec2(20, 15), uv0, uv1);
	ImGui::SameLine();
}

void FileChooser::fillTableRow(const File &file, int index, bool *open)
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

void FileChooser::openPressed(bool *open)
{
	if (m_DirectoryContent[m_SelectedFile].type == std::filesystem::file_type::directory)
	{
		std::filesystem::path path(m_CurrentDirectory);
		m_CurrentDirectory = path.append(m_SelectedFileName);
		m_DirectoryContent = listDirectory(m_CurrentDirectory, m_Hidden);

		resetSelectedFile();
	} else
	{
		*open = false;
	}
}
