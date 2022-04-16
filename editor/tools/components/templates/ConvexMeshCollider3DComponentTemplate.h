//
// Created by david on 12. 04. 2022..
//

#ifndef SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider3DComponentTemplate.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<ConvexMeshCollider3DComponent> : public ComponentTemplate<Collider3DComponent>
	{
	public:
		static void drawComponent(ConvexMeshCollider3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("ConvexMesh collider 3D", visible))
			{
				ImGui::PushID("ConvexMesh3D");
				ComponentTemplate<Collider3DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns(2, nullptr, false);
				EditorUtil::drawColumnInputInt("Number of faces", "##MeshFaces", component.numberOfFaces);
				ImGui::Columns();

				drawVertices(component.vertices);
				drawIndices(component.indices);
			}
		}

	private:
		static void drawVertices(std::vector<float> &vertices)
		{
			setHeaderColorStyle();

			if (ImGui::CollapsingHeader("Vertices")) {
				ImGui::Columns(2, nullptr, false);
				ImGui::Indent();

				for (int i = 0; i < vertices.size() / 3; ++i)
				{
					std::string text = "Point " + std::to_string(i + 1);
					std::string label = "##MeshPoint" + std::to_string(i + 1);

					const int index = i * 3;
					rp3d::Vector3 vec{vertices[index], vertices[index + 1], vertices[index + 2]};

					if (EditorUtil::drawColumnDragFloat3(text.c_str(), label.c_str(), vec))
					{
						vertices[index] = vec.x;
						vertices[index + 1] = vec.y;
						vertices[index + 2] = vec.z;
					}
				}

				ImGui::Unindent();
				ImGui::Columns();
			}

			resetHeaderColorStyle();
		}

		static void drawIndices(std::vector<int> &indices)
		{
			setHeaderColorStyle();

			if (ImGui::CollapsingHeader("Indices")) {
				ImGui::Columns(2, nullptr, false);
				ImGui::Indent();

				for (int i = 0; i < indices.size(); ++i)
				{
					std::string text = "Index " + std::to_string(i + 1);
					std::string label = "##MeshIndex" + std::to_string(i + 1);

					EditorUtil::drawColumnInputInt(text.c_str(), label.c_str(), indices[i]);
				}

				ImGui::Unindent();
				ImGui::Columns();
			}

			resetHeaderColorStyle();
		}

		static void setHeaderColorStyle()
		{
			const ImVec4 windowBg = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
			ImGui::PushStyleColor(ImGuiCol_Header, windowBg);
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, windowBg);
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, windowBg);
		}

		static void resetHeaderColorStyle()
		{
			ImGui::PopStyleColor(3);
		}

	};
}

#endif //SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H
