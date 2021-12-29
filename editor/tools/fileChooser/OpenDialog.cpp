//
// Created by david on 27. 12. 2021..
//

#include "OpenDialog.h"

void Survive::OpenDialog::open(float windowWidth, float windowHeight, bool *open)
{
	drawDialogHeader(windowWidth, windowHeight);

	ImGui::OpenPopup("Open");
	if (ImGui::BeginPopupModal("Open", open, ImGuiWindowFlags_NoDocking))
	{
		drawDialogBody(open, windowHeight);
		drawOpenFilenameTextbox(open);

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(7);
}

void Survive::OpenDialog::drawOpenFilenameTextbox(bool *open)
{
	if (ImGui::BeginChild("open text box"))
	{
		ImGui::InputText("##FilenameTextbox", m_SelectedFileName.data(), BUFFER_SIZE, ImGuiInputTextFlags_ReadOnly);

		drawCancelButton(open);
		if (ImGui::Button("Open"))
		{
			openPressed(open);
		}

		ImGui::EndChild();
	}
}

void Survive::OpenDialog::openPressed(bool *open)
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

void Survive::OpenDialog::fillTableRow(const Survive::File &file, int index, bool *open)
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
		openPressed(open);
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
