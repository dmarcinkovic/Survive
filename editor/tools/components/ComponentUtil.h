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
	public:
		static std::vector<const char *> getListOfComponents()
		{
			std::vector<const char *> components = {
					"Animation component", "Bloom component", "Move component",
					"Reflection component", "Refraction component", "Render2D Component",
					"Render3D component", "Rigid body component", "Shadow component",
					"Sound component", "Sprite component", "Sprite sheet component",
					"Textured component", "Transform3D component"
			};

			return components;
		}

		static void drawAllComponents(entt::registry &registry, entt::entity entity)
		{
			drawComponent<AnimationComponent>(registry, entity);
			drawComponent<BloomComponent>(registry, entity);
			drawComponent<MoveComponent>(registry, entity);
			drawComponent<ReflectionComponent>(registry, entity);
			drawComponent<RefractionComponent>(registry, entity);
			drawComponent<Render2DComponent>(registry, entity);
			drawComponent<Render3DComponent>(registry, entity);
			drawComponent<RigidBodyComponent>(registry, entity);
			drawComponent<ShadowComponent>(registry, entity);
			drawComponent<SoundComponent>(registry, entity);
			drawComponent<SpriteComponent>(registry, entity);
			drawComponent<SpriteSheetComponent>(registry, entity);
			drawComponent<TexturedComponent>(registry, entity);
			drawComponent<Transform3DComponent>(registry, entity);
		}

		static bool addComponent(entt::registry &registry, entt::entity entity, int selectedItem)
		{
			switch (selectedItem)
			{
				case 0:
					return addComponent<AnimationComponent>(registry, entity);
				case 1:
					return addComponent<BloomComponent>(registry, entity);
				case 2:
					return addComponent<MoveComponent>(registry, entity);
				case 3:
					return addComponent<ReflectionComponent>(registry, entity);
				case 4:
					return addComponent<RefractionComponent>(registry, entity);
				case 5:
					return addComponent<Render2DComponent>(registry, entity);
				case 6:
					return addComponent<Render3DComponent>(registry, entity);
				case 7:
					return addComponent<RigidBodyComponent>(registry, entity);
				case 8:
					return addComponent<ShadowComponent>(registry, entity);
				case 9:
					return addComponent<SoundComponent>(registry, entity);
				case 10:
					return addComponent<SpriteComponent>(registry, entity);
				case 11:
					return addComponent<SpriteSheetComponent>(registry, entity);
				case 12:
					return addComponent<TexturedComponent>(registry, entity);
				case 13:
					return addComponent<Transform3DComponent>(registry, entity);
				default:
					throw std::runtime_error("Selected item not implemented");
			}
		}

	private:
		template<typename Component>
		static bool addComponent(entt::registry &registry, entt::entity entity)
		{
			static Component component;

			if (registry.has<Component>(entity))
			{
				ComponentTemplate::drawComponent(registry.get<Component>(entity));
			} else
			{
				ComponentTemplate::drawComponent(component);
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
				if (!registry.has<Component>(entity))
				{
					registry.emplace<Component>(entity, component);
				}

				return true;
			}

			return false;
		}

		template<typename Component>
		static void drawComponent(entt::registry &registry, entt::entity entity)
		{
			if (registry.has<Component>(entity))
			{
				bool visible = true;
				ComponentTemplate::drawComponent(registry.get<Component>(entity), &visible);

				if (!visible)
				{
					registry.remove<Component>(entity);
				}
			}
		}
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
