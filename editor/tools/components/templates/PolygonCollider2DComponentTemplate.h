//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_POLYGONCOLLIDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_POLYGONCOLLIDER2DCOMPONENTTEMPLATE_H

#include <glm/gtc/type_ptr.hpp>

#include "ComponentTemplate.h"
#include "Components.h"
#include "Collider2DComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<PolygonCollider2DComponent> : public ComponentTemplate<Collider2DComponent>
	{
	private:
		Texture m_DeleteIcon;
		Loader m_Loader;

		const ImVec2 m_Uv0;
		const ImVec2 m_Uv1;

	public:
		ComponentTemplate<PolygonCollider2DComponent>()
				: m_Uv0(0, 1), m_Uv1(1, 0)
		{
			m_DeleteIcon = m_Loader.loadTexture("assets/textures/delete_icon.png");
		}

		void drawComponent(PolygonCollider2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Polygon collider 2D", visible))
			{
				addPolygonPoint(component.points, component.polygonShape);

				ImGui::Columns(2, nullptr, false);
				drawPolygonPoints(component.points, component.polygonShape);

				ImGui::Separator();

				ImGui::PushID("Polygon2D");
				ComponentTemplate<Collider2DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns();
			}
		}

	private:
		void drawPolygonPoints(std::vector<b2Vec2> &points, b2PolygonShape &shape)
		{
			int itemToDelete = -1;

			for (int i = 0; i < points.size(); ++i)
			{
				drawPoint(i, points, shape);

				ImGui::PushID(i);

				int result;
				if ((result = drawDeleteButton(i, points, shape)) != -1)
				{
					itemToDelete = result;
				}

				ImGui::PopID();
			}

			if (itemToDelete != -1)
			{
				points.erase(points.begin() + itemToDelete);
			}
		}

		static void drawPoint(int index, std::vector<b2Vec2> &points, b2PolygonShape &shape)
		{
			b2Vec2 &point = points[index];

			const std::string text = "Point" + std::to_string(index + 1);
			const std::string label = "##Polygon p" + std::to_string(index + 1);

			ImGui::TextUnformatted(text.c_str());
			ImGui::NextColumn();

			glm::vec2 vec(points[index].x, points[index].y);

			if (ImGui::DragFloat2(label.c_str(), glm::value_ptr(vec)))
			{
				points[index].x = vec.x;
				points[index].y = vec.y;

				if (points.size() >= 3)
				{
					shape.Set(points.data(), static_cast<int>(points.size()));
				}
			}

			ImGui::SameLine();
		}

		int drawDeleteButton(int index, const std::vector<b2Vec2> &points,
							 b2PolygonShape &shape) const
		{
			int itemToDelete = -1;
			auto icon = reinterpret_cast<ImTextureID>(m_DeleteIcon.textureId());

			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

			float buttonSize = 1.4f * ImGui::GetTextLineHeight();
			if (ImGui::ImageButton(icon, ImVec2(buttonSize, buttonSize), m_Uv0, m_Uv1))
			{
				itemToDelete = index;
				if (points.size() >= 3)
				{
					shape.Set(points.data(), static_cast<int>(points.size()));
				}
			}

			drawTooltip();

			ImGui::PopStyleColor();
			ImGui::NextColumn();

			return itemToDelete;
		}

		static void drawTooltip()
		{
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Delete point");
				ImGui::EndTooltip();
			}
		}

		static void addPolygonPoint(std::vector<b2Vec2> &points, b2PolygonShape &shape)
		{
			ImGui::TextUnformatted("Add new point");
			ImGui::SameLine();
			if (ImGui::Button(" + ") && points.size() < b2_maxPolygonVertices)
			{
				points.emplace_back(0, 0);
				if (points.size() >= 3)
				{
					shape.Set(points.data(), static_cast<int>(points.size()));
				}
			}

			ImGui::Separator();
		}
	};
}

#endif //SURVIVE_POLYGONCOLLIDER2DCOMPONENTTEMPLATE_H
