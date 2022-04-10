//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_TRANSFORM3DCOMPONENTTEMPLATE_H
#define SURVIVE_TRANSFORM3DCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<Transform3DComponent>
	{
	public:
		static void drawComponent(Transform3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Transform3D", visible))
			{
				ImGui::Columns(4);
				drawTransform3DHeader();

				ImGui::Text("Position");
				drawTransform3DRow(component.position, "##PosX", "##PosY", "##PosZ");
				ImGui::Text("Rotation");
				drawTransform3DRow(component.rotation, "##RotX", "##RotY", "##RotZ");
				ImGui::Text("Scale");
				drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ", 0.0f);

				ImGui::Columns();
			}
		}

	private:
		static void drawTransform3DHeader()
		{
			drawTransform2DHeader();
			ImGui::Text("Z");
			ImGui::NextColumn();
		}

		static void drawTransform2DHeader()
		{
			ImGui::NextColumn();
			ImGui::Text("X");
			ImGui::NextColumn();
			ImGui::Text("Y");
			ImGui::NextColumn();
		}

		static void setDragFloat(float &value, const char *label, const ImVec4 &frameBg,
								 const ImVec4 &increment, float lowerBound = std::numeric_limits<float>::min())
		{
			constexpr float upperBound = std::numeric_limits<float>::max();

			ImGui::NextColumn();
			ImGui::PushStyleColor(ImGuiCol_FrameBg, frameBg);

			ImVec4 frameBgHovered = add(frameBg, increment);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, frameBgHovered);

			ImVec4 frameBgActive = add(frameBgHovered, increment);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, frameBgActive);

			ImGui::DragFloat(label, &value, 1.0f, lowerBound, upperBound);
			ImGui::PopStyleColor(3);
		}

		static void drawTransform3DRow(glm::vec3 &vec, const char *x, const char *y, const char *z,
									   float lowerBound = std::numeric_limits<float>::lowest())
		{
			setDragFloat(vec.x, x, ImVec4(0.5f, 0, 0, 1), ImVec4(0.25f, 0, 0, 1), lowerBound);
			setDragFloat(vec.y, y, ImVec4(0, 0.4f, 0, 1), ImVec4(0, 0.2f, 0, 1), lowerBound);
			setDragFloat(vec.z, z, ImVec4(0, 0, 0.5f, 1), ImVec4(0, 0, 0.25f, 1), lowerBound);

			ImGui::NextColumn();
		}

		static ImVec4 add(const ImVec4 &vec1, const ImVec4 &vec2)
		{
			return {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w};
		}
	};
}

#endif //SURVIVE_TRANSFORM3DCOMPONENTTEMPLATE_H
