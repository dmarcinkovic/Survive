//
// Created by david on 07. 10. 2021..
//

#include "CameraWindow.h"
#include "EditorUtil.h"

void Survive::CameraWindow::draw(Camera &camera)
{
	setColors();
	drawHeader();

	drawCameraProperties(camera);
	drawCameraTransform(camera);

	ImGui::PopStyleColor(3);
}

void Survive::CameraWindow::setColors()
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
}

void Survive::CameraWindow::drawHeader()
{
	ImGui::TextUnformatted("Camera");
	ImGui::Separator();
}

void Survive::CameraWindow::drawCameraTransform(Camera &camera)
{
	ImGui::Separator();

	ImGui::Columns(4);
	EditorUtil::drawTransform3DHeader();

//	ImGui::Text("Position");
//	EditorUtil::drawTransform3DRow(camera.getPosition(), "##CPosX", "##CPosY", "##CPosZ");
	ImGui::Text("Rotation");
	EditorUtil::drawTransform3DRow(camera.rotation, "##CRotX", "##CRotY", "##CRotZ");

	ImGui::Columns();
}

void Survive::CameraWindow::drawCameraProperties(Camera &camera)
{
	ImGui::Columns(2, nullptr, false);

	ImGui::TextUnformatted("Field of View");
	ImGui::NextColumn();
	ImGui::SetNextItemWidth(-1.0f);
	ImGui::InputFloat("##Input field of view", &camera.fieldOfView);
	ImGui::NextColumn();

	drawClipPlanes(camera);

	showCameraProperties(camera);

	ImGui::Columns();
}

void Survive::CameraWindow::drawClipPlanes(Camera &camera)
{
	ImGui::TextUnformatted("Clipping planes");
	ImGui::NextColumn();
	ImGui::NextColumn();

	ImGui::Indent();

	EditorUtil::drawColumnInputFloat("Near", "##Near", camera.near);
	EditorUtil::drawColumnInputFloat("Far", "##Far", camera.far);

	ImGui::Unindent();
}

void Survive::CameraWindow::showCameraProperties(Survive::Camera &camera)
{
	ImGui::TextUnformatted("Camera properties");
	ImGui::NextColumn();
	ImGui::NextColumn();
	ImGui::Indent();

	float pitch = camera.getPitch();
	if (EditorUtil::drawColumnInputFloat("Pitch", "##Camera pitch", pitch, -90, 90))
	{
		camera.setPitch(pitch);
	}

	float yaw = camera.getYaw();
	if (EditorUtil::drawColumnInputFloat("Yaw", "##Camera yaw", yaw, -90, 90))
	{
		camera.setYaw(yaw);
	}

	ImGui::Unindent();
}
