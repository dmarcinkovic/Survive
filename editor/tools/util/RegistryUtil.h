//
// Created by david on 23. 10. 2021..
//

#ifndef SURVIVE_REGISTRYUTIL_H
#define SURVIVE_REGISTRYUTIL_H

#include "entt.hpp"
#include "Components.h"

namespace Survive
{
	class RegistryUtil
	{
	private:
		using Storage = std::tuple<Transform3DComponent, SpriteSheetComponent, RigidBody2DComponent>;

		std::unordered_map<int, Storage> m_Components;

	public:
		template<typename Component, typename... Components>
		void store(entt::registry &registry)
		{
			storeComponent<Component>(registry);
			if constexpr(sizeof...(Components) != 0)
			{
				store<Components...>(registry);
			}
		}

		template<typename Component, typename... Components>
		void restore(entt::registry &registry)
		{
			restoreComponent<Component>(registry);
			if constexpr(sizeof...(Components) != 0)
			{
				restore<Components...>(registry);
			}
		}

	private:
		template<typename Component>
		void storeComponent(entt::registry &registry)
		{
			auto view = registry.view<Component>();

			for (auto const entity: view)
			{
				storeComponents(entity, registry);
			}
		}

		template<typename Components>
		void restoreComponent(entt::registry &registry)
		{
			auto view = registry.view<Components>();

			for (auto const entity: view)
			{
				restoreComponents(entity, registry);
			}
		}

		void storeComponents(entt::entity entity, entt::registry &registry)
		{
			auto index = static_cast<int>(entity);
			Storage &storage = m_Components[index];

			save<Transform3DComponent>(registry, entity, storage);
			save<SpriteSheetComponent>(registry, entity, storage);
			save<RigidBody2DComponent>(registry, entity, storage);
		}

		void restoreComponents(entt::entity entity, entt::registry &registry)
		{
			auto index = static_cast<int>(entity);
			const Storage &storage = m_Components[index];

			replace<Transform3DComponent>(registry, entity, storage);
			replace<SpriteSheetComponent>(registry, entity, storage);
			replace<RigidBody2DComponent>(registry, entity, storage);
		}

		template<typename Component>
		void save(entt::registry &registry, entt::entity entity, Storage &storage)
		{
			if (registry.any_of<Component>(entity))
			{
				auto &component = std::get<Component>(storage);
				component = registry.get<Component>(entity);
			}
		}

		template<typename Component>
		void replace(entt::registry &registry, entt::entity entity, const Storage &storage)
		{
			if (registry.any_of<Component>(entity))
			{
				registry.replace<Component>(entity, std::get<Component>(storage));
			}
		}
	};
}

#endif //SURVIVE_REGISTRYUTIL_H
