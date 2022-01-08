//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_COMPONENTUTIL_H
#define SURVIVE_COMPONENTUTIL_H

#include <string>

#include "entt.hpp"
#include "Components.h"
#include "ComponentTemplate.h"

namespace Survive
{
	class ComponentUtil
	{
	private:
		ComponentTemplate m_ComponentTemplate;

	public:
		[[nodiscard]] bool isUsingKeyEvents() const
		{
			return m_ComponentTemplate.isUsingKeyEvents();
		}

		static std::vector<const char *> getListOfComponents()
		{
			std::vector<const char *> components = {
					"Animation component", "Bloom component", "Box Collider2D component", "Box Collider3D component",
					"Capsule Collider3D component", "Circle Collider2D component", "Edge Collider2D component",
					"Polygon Collider2D component", "Reflection component", "Refraction component",
					"Render2D Component", "Render3D component", "RigidBody2D component", "RigidBody3D component",
					"Rigid body component", "Shadow component", "Sound component", "Sphere Collider3D component",
					"Sprite component", "Sprite sheet component", "Text Component", "Transform3D component"
			};

			return components;
		}

		void drawAllComponents(entt::registry &registry, entt::entity entity)
		{
			drawComponent<AnimationComponent>(registry, entity);
			drawComponent<BloomComponent>(registry, entity);
			drawComponent<BoxCollider2DComponent>(registry, entity);
			drawComponent<BoxCollider3DComponent>(registry, entity);
			drawComponent<CapsuleCollider3DComponent>(registry, entity);
			drawComponent<CircleCollider2DComponent>(registry, entity);
			drawComponent<EdgeCollider2DComponent>(registry, entity);
			drawComponent<PolygonCollider2DComponent>(registry, entity);
			drawComponent<ReflectionComponent>(registry, entity);
			drawComponent<RefractionComponent>(registry, entity);
			drawComponent<Render2DComponent>(registry, entity);
			drawComponent<Render3DComponent>(registry, entity);
			drawComponent<RigidBody2DComponent>(registry, entity);
			drawComponent<RigidBody3DComponent>(registry, entity);
			drawComponent<RigidBodyComponent>(registry, entity);
			drawComponent<ShadowComponent>(registry, entity);
			drawComponent<SoundComponent>(registry, entity);
			drawComponent<SphereCollider3DComponent>(registry, entity);
			drawComponent<SpriteComponent>(registry, entity);
			drawComponent<SpriteSheetComponent>(registry, entity);
			drawComponent<TextComponent>(registry, entity);
			drawComponent<Transform3DComponent>(registry, entity);
		}

		bool addComponent(entt::registry &registry, entt::entity entity, int selectedItem)
		{
			switch (selectedItem)
			{
				case 0:
					return addComponent<AnimationComponent>(registry, entity);
				case 1:
					return addComponent<BloomComponent>(registry, entity);
				case 2:
					return addComponent<BoxCollider2DComponent>(registry, entity);
				case 3:
					return addComponent<BoxCollider3DComponent>(registry, entity);
				case 4:
					return addComponent<CapsuleCollider3DComponent>(registry, entity);
				case 5:
					return addComponent<CircleCollider2DComponent>(registry, entity);
				case 6:
					return addComponent<EdgeCollider2DComponent>(registry, entity);
				case 7:
					return addComponent<PolygonCollider2DComponent>(registry, entity);
				case 8:
					return addComponent<ReflectionComponent>(registry, entity);
				case 9:
					return addComponent<RefractionComponent>(registry, entity);
				case 10:
					return addComponent<Render2DComponent>(registry, entity);
				case 11:
					return addComponent<Render3DComponent>(registry, entity);
				case 12:
					return addComponent<RigidBody2DComponent>(registry, entity);
				case 13:
					return addComponent<RigidBody3DComponent>(registry, entity);
				case 14:
					return addComponent<RigidBodyComponent>(registry, entity);
				case 15:
					return addComponent<ShadowComponent>(registry, entity);
				case 16:
					return addComponent<SoundComponent>(registry, entity);
				case 17:
					return addComponent<SphereCollider3DComponent>(registry, entity);
				case 18:
					return addComponent<SpriteComponent>(registry, entity);
				case 19:
					return addComponent<SpriteSheetComponent>(registry, entity);
				case 20:
					return addComponent<TextComponent>(registry, entity);
				case 21:
					return addComponent<Transform3DComponent>(registry, entity);
				default:
					throw std::runtime_error("Selected item not implemented");
			}
		}

	private:
		template<typename Component>
		bool addComponent(entt::registry &registry, entt::entity entity)
		{
			static Component component;

			if (registry.any_of<Component>(entity))
			{
				m_ComponentTemplate.drawComponent(registry.get<Component>(entity));
			} else
			{
				m_ComponentTemplate.drawComponent(component);
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
		void drawComponent(entt::registry &registry, entt::entity entity)
		{
			if (registry.any_of<Component>(entity))
			{
				bool visible = true;
				m_ComponentTemplate.drawComponent(registry.get<Component>(entity), &visible);

				if (!visible)
				{
					registry.remove<Component>(entity);
				}
			}
		}
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
