//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <iostream>

#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open()
{
	auto[width, height] = Display::getWindowSize<float>();
	static std::vector<File> currentDirectory = listDirectory("/home/david");

	ImGui::SetNextWindowSize(ImVec2{width / 2.0f, height / 2.0f}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	bool p_open = true;
	if (ImGui::Begin("Example: Simple layout", &p_open, ImGuiWindowFlags_MenuBar))
	{
		// Left
		static int selected = 0;
		{
			static ImGuiTableFlags flags =
					ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable |
					ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

			const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
			if (ImGui::BeginTable("##3ways", 3, flags))
			{
				ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
				ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
				ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
				ImGui::TableHeadersRow();

				ImGui::EndTable();
			}

			if (ImGui::BeginChild("table_pane"))
			{
				if (ImGui::BeginTable("###3ways", 3, flags))
				{
					for (int i = 0; i < currentDirectory.size(); ++i)
					{
						const File &file = currentDirectory[i];
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						if (ImGui::Selectable(file.name.c_str(), selected == i))
						{
							selected = i;
						}

						ImGui::TableNextColumn();
						if (ImGui::Selectable(getFileSize(file.size).c_str(), selected == i))
						{
							selected = i;
						}

						ImGui::TableNextColumn();
						if (ImGui::Selectable(getFileType(file.type), selected == i))
						{
							selected = i;
						}
					}
					ImGui::EndTable();
				}
				ImGui::EndChild();
			}

		}
		ImGui::SameLine();
	}
	ImGui::End();
}

std::vector<File> FileChooser::listDirectory(const std::string &directory)
{
	std::filesystem::directory_iterator directoryIterator(directory);
	std::vector<File> files;

	for (auto const &path : directoryIterator)
	{
		File file;
		file.name = path.path().filename();

		if (path.is_regular_file())
		{
			file.size = path.file_size();
		}

		file.type = path.status().type();
		files.emplace_back(file);
	}

	return files;
}

std::vector<File> FileChooser::listCurrentDirectory()
{
	auto workingDirectory = std::filesystem::current_path();

	return listDirectory(std::filesystem::absolute(workingDirectory));
}

std::string FileChooser::getFileSize(unsigned long fileSize)
{
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
