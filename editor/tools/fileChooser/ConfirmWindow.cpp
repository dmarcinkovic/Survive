//
// Created by david on 12. 07. 2021..
//

#include "ConfirmWindow.h"

bool ConfirmWindow::draw(float width, float height, float parentWidth, float parentHeight)
{
	if (m_Confirm)
	{
		ImGui::OpenPopup("Confirm");
	}

	setWindowProperties(width, height, parentWidth, parentHeight);
	setColorStyle();

	if (ImGui::BeginPopupModal("Confirm", &m_Confirm, ImGuiWindowFlags_NoDocking))
	{
		drawScaledText();
		drawButtons(width, height);

		ImGui::EndPopup();
	}
	ImGui::PopStyleColor(3);

	return m_Result;
}

void ConfirmWindow::openConfirmWindow()
{
	m_Confirm = true;
	m_Result = false;
}

ImVec2 ConfirmWindow::calcNextWindowPos(const ImVec2 &size, float parentWidth, float parentHeight)
{
	ImVec2 currentPosition = ImGui::GetWindowPos();
	ImVec2 offset(parentWidth / 2.0f - size.x / 2.0f, parentHeight / 2.0f - size.y / 2.0f);

	return ImVec2(currentPosition.x + offset.x, currentPosition.y + offset.y);
}

void ConfirmWindow::setWindowProperties(float width, float height, float parentWidth, float parentHeight)
{
	const ImVec2 size(width, height);

	ImGui::SetNextWindowSize(size, ImGuiCond_Once);
	ImGui::SetNextWindowPos(calcNextWindowPos(size, parentWidth, parentHeight), ImGuiCond_Once);
}

void ConfirmWindow::setColorStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.35f, 0.35f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
}

void ConfirmWindow::drawScaledText()
{
	ImGui::SetWindowFontScale(1.1);
	ImGui::Text("File already exists. Do you want to replace it?");
	ImGui::SetWindowFontScale(1.0f);
}

void ConfirmWindow::drawButtons(float width, float height)
{
	if (ImGui::Button("Yes", ImVec2(width / 2.0f, height / 3.5f)))
	{
		m_Confirm = false;
		m_Result = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Cancel", ImVec2(width / 2.0f, height / 3.5f)))
	{
		m_Confirm = false;
	}
}
