//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_COMPONENTUTIL_H
#define SURVIVE_COMPONENTUTIL_H

#include <string>

#include "entt.hpp"
#include "Components.h"
#include "ComponentTemplates.h"

namespace Survive
{
	class ComponentUtil
	{
	private:
		ComponentTemplate<AnimationComponent> m_AnimationTemplate;
		ComponentTemplate<BoxCollider2DComponent> m_BoxCollider2DTemplate;
		ComponentTemplate<BloomComponent> m_BloomTemplate;
		ComponentTemplate<CircleCollider2DComponent> m_CircleCollider2DTemplate;
		ComponentTemplate<DistanceJoint2DComponent> m_DistanceJoint2DTemplate;
		ComponentTemplate<EdgeCollider2DComponent> m_EdgeCollider2DTemplate;
		ComponentTemplate<HingeJoint2DComponent> m_HingeJoint2DTemplate;
		ComponentTemplate<MaterialComponent> m_MaterialTemplate;
		ComponentTemplate<PolygonCollider2DComponent> m_PolygonCollider2DTemplate;
		ComponentTemplate<ReflectionComponent> m_ReflectionTemplate;
		ComponentTemplate<RefractionComponent> m_RefractionTemplate;
		ComponentTemplate<Render2DComponent> m_Render2DTemplate;
		ComponentTemplate<Render3DComponent> m_Render3dTemplate;
		ComponentTemplate<RigidBody2DComponent> m_RigidBody2DTemplate;
		ComponentTemplate<ScriptComponent> m_ScripTemplate;
		ComponentTemplate<ShadowComponent> m_ShadowTemplate;
		ComponentTemplate<SoundComponent> m_SoundTemplate;
		ComponentTemplate<SpriteComponent> m_SpriteTemplate;
		ComponentTemplate<SpriteSheetComponent> m_SpriteSheetTemplate;
		ComponentTemplate<TextComponent> m_TextTemplate;
		ComponentTemplate<Transform3DComponent> m_TransformTemplate;

	public:
		[[nodiscard]] bool isUsingKeyEvents() const
		{
			return m_TextTemplate.isUsingKeyEvents();
		}

		static std::vector<const char *> getListOfComponents()
		{
			std::vector<const char *> components = {
					"Animation component", "Box Collider2D component", "Bloom component", "Circle Collider2D component",
					"Distance Joint2D component", "Edge Collider2D component", "Hinge Joint2D component",
					"Material component", "PolygonCollider2D component", "Reflection component", "Refraction component",
					"Render2D Component", "Render3D component", "RigidBody2D component", "Script component",
					"Shadow component", "Sound component", "Sprite component", "Sprite sheet component",
					"Text Component", "Transform3D component"
			};

			return components;
		}

		void drawAllComponents(entt::registry &registry, entt::entity entity)
		{
			drawComponent(registry, entity, m_AnimationTemplate);
			drawComponent(registry, entity, m_BoxCollider2DTemplate);
			drawComponent(registry, entity, m_BloomTemplate);
			drawComponent(registry, entity, m_CircleCollider2DTemplate);
			drawComponent(registry, entity, m_DistanceJoint2DTemplate);
			drawComponent(registry, entity, m_EdgeCollider2DTemplate);
			drawComponent(registry, entity, m_HingeJoint2DTemplate);
			drawComponent(registry, entity, m_MaterialTemplate);
			drawComponent(registry, entity, m_PolygonCollider2DTemplate);
			drawComponent(registry, entity, m_ReflectionTemplate);
			drawComponent(registry, entity, m_RefractionTemplate);
			drawComponent(registry, entity, m_Render2DTemplate);
			drawComponent(registry, entity, m_Render3dTemplate);
			drawComponent(registry, entity, m_RigidBody2DTemplate);
			drawComponent(registry, entity, m_ScripTemplate);
			drawComponent(registry, entity, m_ShadowTemplate);
			drawComponent(registry, entity, m_SoundTemplate);
			drawComponent(registry, entity, m_SpriteTemplate);
			drawComponent(registry, entity, m_SpriteSheetTemplate);
			drawComponent(registry, entity, m_TextTemplate);
			drawComponent(registry, entity, m_TransformTemplate);
		}

		bool addComponent(entt::registry &registry, entt::entity entity, int selectedItem)
		{
			switch (selectedItem)
			{
				case 0:
					return addComponent(registry, entity, m_AnimationTemplate);
				case 1:
					return addComponent(registry, entity, m_BoxCollider2DTemplate);
				case 2:
					return addComponent(registry, entity, m_BloomTemplate);
				case 3:
					return addComponent(registry, entity, m_CircleCollider2DTemplate);
				case 4:
					return addComponent(registry, entity, m_DistanceJoint2DTemplate);
				case 5:
					return addComponent(registry, entity, m_EdgeCollider2DTemplate);
				case 6:
					return addComponent(registry, entity, m_HingeJoint2DTemplate);
				case 7:
					return addComponent(registry, entity, m_MaterialTemplate);
				case 8:
					return addComponent(registry, entity, m_PolygonCollider2DTemplate);
				case 9:
					return addComponent(registry, entity, m_ReflectionTemplate);
				case 10:
					return addComponent(registry, entity, m_RefractionTemplate);
				case 11:
					return addComponent(registry, entity, m_Render2DTemplate);
				case 12:
					return addComponent(registry, entity, m_Render3dTemplate);
				case 13:
					return addComponent(registry, entity, m_RigidBody2DTemplate);
				case 14:
					return addComponent(registry, entity, m_ScripTemplate);
				case 15:
					return addComponent(registry, entity, m_ShadowTemplate);
				case 16:
					return addComponent(registry, entity, m_SoundTemplate);
				case 17:
					return addComponent(registry, entity, m_SpriteTemplate);
				case 18:
					return addComponent(registry, entity, m_SpriteSheetTemplate);
				case 19:
					return addComponent(registry, entity, m_TextTemplate);
				case 20:
					return addComponent(registry, entity, m_TransformTemplate);
				default:
					throw std::runtime_error("Selected item not implemented");
			}
		}

	private:
		template<typename Component>
		static bool addComponent(entt::registry &registry, entt::entity entity,
						  ComponentTemplate<Component> &componentTemplate)
		{
			static Component component;

			if (registry.any_of<Component>(entity))
			{
				componentTemplate.drawComponent(registry.get<Component>(entity), nullptr);
			} else
			{
				componentTemplate.drawComponent(component, nullptr);
			}

			if (drawAddButton(registry, entity, component))
			{
				component = Component{};
				return true;
			}

			return false;
		}

		template<typename Component>
		static bool drawAddButton(entt::registry &registry, entt::entity entity, Component &component)
		{
			float width = ImGui::GetColumnWidth() * 0.7f;
			float height = 2.0f * ImGui::GetFontSize();

			if (ImGui::Button("Add component", ImVec2(width, height)))
			{
				if (!registry.any_of<Component>(entity))
				{
					registry.emplace<Component>(entity, component);
				}

				return true;
			}

			return false;
		}

		template<typename Component>
		static void drawComponent(entt::registry &registry, entt::entity entity,
						   ComponentTemplate<Component> &componentTemplate)
		{
			if (registry.any_of<Component>(entity))
			{
				bool visible = true;
				componentTemplate.drawComponent(registry.get<Component>(entity), &visible);

				if (!visible)
				{
					registry.remove<Component>(entity);
				}
			}
		}
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
