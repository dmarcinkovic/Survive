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
			ComponentTemplate::drawComponent<AnimationComponent>(registry, entity);
			ComponentTemplate::drawComponent<BloomComponent>(registry, entity);
			ComponentTemplate::drawComponent<MoveComponent>(registry, entity);
			ComponentTemplate::drawComponent<ReflectionComponent>(registry, entity);
			ComponentTemplate::drawComponent<RefractionComponent>(registry, entity);
			ComponentTemplate::drawComponent<RenderComponent>(registry, entity);
			ComponentTemplate::drawComponent<RigidBodyComponent>(registry, entity);
			ComponentTemplate::drawComponent<ShadowComponent>(registry, entity);
			ComponentTemplate::drawComponent<SoundComponent>(registry, entity);
			ComponentTemplate::drawComponent<SpriteComponent>(registry, entity);
			ComponentTemplate::drawComponent<SpriteSheetComponent>(registry, entity);
			ComponentTemplate::drawComponent<TexturedComponent>(registry, entity);
			ComponentTemplate::drawComponent<Transform2DComponent>(registry, entity);
			ComponentTemplate::drawComponent<Transform3DComponent>(registry, entity);
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
			if (!registry.has<Component>(entity))
			{
				registry.emplace<Component>(entity);
			}

			ComponentTemplate::drawComponent<Component>(registry, entity);
		}
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
