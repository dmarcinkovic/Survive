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
	};
}

#endif //SURVIVE_COMPONENTUTIL_H
