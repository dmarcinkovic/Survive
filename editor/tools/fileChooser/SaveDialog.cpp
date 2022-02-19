//
// Created by david on 27. 12. 2021..
//

#include "SaveDialog.h"

void Survive::SaveDialog::open(float windowWidth, float windowHeight, bool *open)
{
	drawDialogHeader(windowWidth, windowHeight);

	ImGui::OpenPopup("Save");
	if (ImGui::BeginPopupModal("Save", open, ImGuiWindowFlags_NoDocking))
	{
		drawDialogBody(open, windowHeight);
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

void Survive::SaveDialog::drawSaveFilenameTextbox(bool *open)
{
	if (ImGui::BeginChild("save text box"))
	{
		char buffer[BUFFER_SIZE]{};

		m_SelectedFile = -1;
		if (!m_SelectedFileName.empty())
		{
			strcpy(buffer, m_SelectedFileName.c_str());
		}

		ImGui::InputText("##SaveTextBoxInput", buffer, BUFFER_SIZE);
		m_SelectedFileName = std::string(buffer);

		drawCancelButton(open);
		if (ImGui::Button("Save"))
		{
			savePressed(open);
		}

		ImGui::EndChild();
	}
}

void Survive::SaveDialog::savePressed(bool *open)
{
	if (directoryChosen())
	{
		buttonDoublePress();
		return;
	}

	std::filesystem::path path = m_CurrentDirectory;
	std::string file = path.append(m_SelectedFileName).string();

	if (std::filesystem::exists(file))
	{
		m_ConfirmWindow.openConfirmWindow();
	} else
	{
		*open = false;
		m_OpenedFile = true;
	}
}

void Survive::SaveDialog::fillTableRow(const Survive::File &file, int index, bool *open)
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
		savePressed(open);
	}

	drawTableColumns(file, index);
}
