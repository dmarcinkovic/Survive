//
// Created by david on 18. 07. 2021..
//

#ifndef SURVIVE_COMPONENTSERIALIZER_H
#define SURVIVE_COMPONENTSERIALIZER_H

#include <fstream>

#include "entt.hpp"

namespace Survive
{
	class ComponentSerializer
	{
	public:
		void saveAnimationComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveBloomComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveReflectionComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveRefractionComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveRender2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveRender3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveRigidBodyComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveShadowComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveSoundComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveSpriteComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveSpriteSheetComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		void saveTransform3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);
	};
}

#endif //SURVIVE_COMPONENTSERIALIZER_H
