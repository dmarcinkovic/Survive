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
	private:
		Texture m_DeleteIcon;
		Loader m_Loader;

	public:
		ComponentTemplate<ConvexMeshCollider3DComponent>()
		{
			m_DeleteIcon = m_Loader.loadTexture("assets/textures/delete_icon.png");
		}

		void drawComponent(ConvexMeshCollider3DComponent &component, bool *visible)
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

				ImGui::Separator();

				drawIndices(component.indices);
			}
		}

	private:
		void drawVertices(std::vector<float> &vertices)
		{
			setHeaderColorStyle();
			addNewVertex(vertices);

			if (ImGui::CollapsingHeader("Vertices")) {
				ImGui::Columns(3, nullptr, false);
				ImGui::Indent();

				int vertexToDelete = -1;
				drawVertexPoints(vertices, vertexToDelete);

				ImGui::Unindent();
				ImGui::Columns();

				if (vertexToDelete != -1)
				{
					vertices.erase(vertices.begin() + vertexToDelete);
					vertices.erase(vertices.begin() + vertexToDelete);
					vertices.erase(vertices.begin() + vertexToDelete);
				}
			}

			resetHeaderColorStyle();
		}

		void drawVertexPoints(std::vector<float> &vertices, int &itemToDelete)
		{
			for (int i = 0; i < vertices.size() / 3; ++i)
			{
				std::string text = "Point " + std::to_string(i + 1);
				std::string label = "##MeshPoint" + std::to_string(i + 1);

				const int index = i * 3;
				drawVertex(vertices, index, text.c_str(), label.c_str());

				ImGui::PushID(i);
				int result = EditorUtil::drawDeleteButton(index, m_DeleteIcon, "Delete vertex");

				if (result != -1)
				{
					itemToDelete = result;
				}

				ImGui::PopID();
			}
		}

		static void drawVertex(std::vector<float> &vertices, int index, const char *text, const char *label)
		{
			rp3d::Vector3 vec{vertices[index], vertices[index + 1], vertices[index + 2]};

			// TODO check for PolyhedronMesh.cpp. 127: Assertion:

			if (EditorUtil::drawColumnDragFloat3(text, label, vec))
			{
				vertices[index] = vec.x;
				vertices[index + 1] = vec.y;
				vertices[index + 2] = vec.z;
			}

			ImGui::SameLine();
		}

		static void drawIndices(std::vector<int> &indices)
		{
			setHeaderColorStyle();
			addNewIndex(indices);

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

		static void addNewVertex(std::vector<float> &vertices)
		{
			ImGui::TextUnformatted("Add new vertex");
			ImGui::SameLine();

			ImGui::PushID("Mesh Add new Vertex");
			if (ImGui::Button(" + "))
			{
				vertices.emplace_back(0.0f);
				vertices.emplace_back(0.0f);
				vertices.emplace_back(0.0f);
			}

			ImGui::PopID();

			ImGui::Separator();
		}

		static void addNewIndex(std::vector<int> &indices)
		{
			ImGui::TextUnformatted("Add new index");
			ImGui::SameLine();

			ImGui::PushID("Mesh Add New Index");
			if (ImGui::Button(" + "))
			{
				indices.emplace_back(0);
			}

			ImGui::PopID();

			ImGui::Separator();
		}
	};
}

#endif //SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H
