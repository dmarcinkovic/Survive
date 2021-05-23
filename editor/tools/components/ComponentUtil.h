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
					"Reflection component", "Refraction component", "Render component",
					"Rigid body component", "Shadow component", "Sound component",
					"Sprite component", "Sprite sheet component", "Textured component",
					"Transform2D component", "Transform3D component"
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
			drawComponent<RenderComponent>(registry, entity);
			drawComponent<RigidBodyComponent>(registry, entity);
			drawComponent<ShadowComponent>(registry, entity);
			drawComponent<SoundComponent>(registry, entity);
			drawComponent<SpriteComponent>(registry, entity);
			drawComponent<SpriteSheetComponent>(registry, entity);
			drawComponent<TexturedComponent>(registry, entity);
			drawComponent<Transform2DComponent>(registry, entity);
			drawComponent<Transform3DComponent>(registry, entity);
		}

		static void addComponent(entt::registry &registry, entt::entity entity, int selectedItem)
		{
			switch (selectedItem)
			{
				case 0:
					addComponent<AnimationComponent>(registry, entity);
					break;
				case 1:
					addComponent<BloomComponent>(registry, entity);
					break;
				case 2:
					addComponent <MoveComponent>(registry, entity);
					break;
				case 3:
					addComponent<ReflectionComponent>(registry, entity);
					break;
				case 4:
					addComponent<RefractionComponent>(registry, entity);
					break;
				case 5:
					addComponent<RenderComponent>(registry, entity);
					break;
				case 6:
					addComponent<RigidBodyComponent>(registry, entity);
					break;
				case 7:
					addComponent<ShadowComponent>(registry, entity);
					break;
				case 8:
					addComponent<SoundComponent>(registry, entity);
					break;
				case 9:
					addComponent<SpriteComponent>(registry, entity);
					break;
				case 10:
					addComponent<SpriteSheetComponent>(registry, entity);
					break;
				case 11:
					addComponent<TexturedComponent>(registry, entity);
					break;
				case 12:
					addComponent<Transform2DComponent>(registry, entity);
					break;
				case 13:
					addComponent<Transform3DComponent>(registry, entity);
					break;
				default:
					throw std::runtime_error("Selected item not implemented");
			}
		}

	private:
		template<typename Component>
		static void addComponent(entt::registry &registry, entt::entity entity)
		{
			static Component component;

			if (registry.has<Component>(entity))
			{
				ComponentTemplate::drawComponent(registry.get<Component>(entity));
			} else
			{
				ComponentTemplate::drawComponent(component);
			}

			ImGui::Columns();
			drawAddButton(registry, entity, component);
		}

		template<typename Component>
		static void drawAddButton(entt::registry &registry, entt::entity entity, Component &component)
		{
			float width = ImGui::GetColumnWidth() * 0.7f;
			float height = 2.0f * ImGui::GetFontSize();

			if (ImGui::Button("Add component", ImVec2(width, height)))
			{
				if (!registry.has<Component>(entity))
				{
					registry.emplace<Component>(entity, component);
				}
			}
		}

		template<typename Component>
		static void drawComponent(entt::registry &registry, entt::entity entity)
		{
			if (registry.has<Component>(entity))
			{
				ComponentTemplate::drawComponent(registry.get<Component>(entity));
			}
		}
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
