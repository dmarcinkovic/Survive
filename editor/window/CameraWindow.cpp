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
	glm::vec3 cameraPosition = camera.getPosition();
	if (EditorUtil::drawColumnDragFloat3("Camera position", "##CameraPosition", cameraPosition))
	{
		camera.setPosition(cameraPosition);
	}
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
	constexpr float min = std::numeric_limits<float>::lowest();
	ImGui::TextUnformatted("Camera properties");
	ImGui::NextColumn();
	ImGui::NextColumn();
	ImGui::Indent();

	float pitch = camera.getPitch();
	if (EditorUtil::drawColumnInputFloat("Pitch", "##Camera pitch", pitch, min))
	{
		if (pitch < -360 || pitch > 360)
		{
			pitch = clampAngle(pitch);
		}

		camera.setPitch(pitch);
	}

	float yaw = camera.getYaw();
	if (EditorUtil::drawColumnInputFloat("Yaw", "##Camera yaw", yaw, min))
	{
		if (yaw < -360 || yaw > 360)
		{
			yaw = clampAngle(yaw);
		}

		camera.setYaw(yaw);
	}

	ImGui::Unindent();
}

float Survive::CameraWindow::clampAngle(float angle)
{
	float factor = std::floor(angle / 360);
	return angle - factor * 360;
}
