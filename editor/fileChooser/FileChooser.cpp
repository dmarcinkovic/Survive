//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <iostream>

#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open(GLuint directoryIcon, GLuint fileIcon, GLuint symlinkIcon)
{
	auto[width, height] = Display::getWindowSize<float>();
	static std::vector<File> currentDirectory = listDirectory("/home/david");

	float windowWidth = width / 2.0f;
	float windowHeight = height / 2.0f;

	ImGui::SetNextWindowSize(ImVec2{windowWidth, windowHeight}, ImGuiCond_Once);
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

			if (ImGui::BeginChild("table_pane", ImVec2{0, windowHeight * 0.7f}))
			{
				if (ImGui::BeginTable("###3ways", 3, flags))
				{
					for (int i = 0; i < currentDirectory.size(); ++i)
					{
						const File &file = currentDirectory[i];
						ImGui::TableNextRow();

						ImGui::TableNextColumn();

						ImVec2 uv0(0.0f,1.0f);
						ImVec2 uv1(1.0f,0.0f);
						auto textureId = reinterpret_cast<ImTextureID>(directoryIcon);
						ImGui::Image(textureId, ImVec2(20, 15), uv0, uv1);
						ImGui::SameLine();

						if (ImGui::Selectable(file.name.c_str(), selected == i))
						{
							selected = i;
						}

						ImGui::TableNextColumn();
						if (ImGui::Selectable(getFileSize(file.size, file.type).c_str(), selected == i))
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

			if (ImGui::BeginChild("text box"))
			{
				ImGuiStyle *style = &ImGui::GetStyle();
				ImVec4 *colors = style->Colors;

				colors[ImGuiCol_WindowBg] = ImVec4(0.267f, 0.267f, 0.267f, 1.0f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.0f);

				char *buf;
				std::string selectedFile = currentDirectory[selected].name;
				buf = selectedFile.data();

				ImGui::InputText("", buf, 255);

				ImGui::SameLine();

				colors[ImGuiCol_Button] = ImVec4(0.345f, 0.345f, 0.345f, 1.0f);
				ImGui::Button("Cancel");

				ImGui::SameLine();

				colors[ImGuiCol_Button] = ImVec4(0.337f, 0.5f, 0.76f, 1.0f);
				ImGui::Button("Open");

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
