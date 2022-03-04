//
// Created by david on 26. 02. 2022..
//

#include "ScriptComponent.h"
#include "ScriptingSystem.h"

void Survive::ScriptingSystem::init(entt::registry &registry, EventHandler &eventHandler)
{
	auto view = registry.view<ScriptComponent>();

	for (entt::entity entity: view)
	{
		ScriptComponent &script = view.get<ScriptComponent>(entity);

		if (script.script != nullptr)
		{
			script.script->init(registry, entity, eventHandler);

			script.script->start();
			EventHandler::addMouseListener([&](int, int, double, double) {
				script.script->onMouseClick();
			});
			EventHandler::addKeyListener([&](int, int) {
				script.script->onKeyboardPressed();
			});
		}
	}
}

void Survive::ScriptingSystem::update(entt::registry &registry)
{
	registry.view<ScriptComponent>().each([](ScriptComponent &script) {
		if (script.script)
		{
			script.script->update();
		}
	});
}

void Survive::ScriptingSystem::destroy(entt::registry &registry)
{
	registry.view<ScriptComponent>().each([](ScriptComponent &script) {
		if (script.script)
		{
			script.script->onDestroy();

			if (script.script->m_NeedRestore)
			{
				script.script->restoreEntity();
			}
		}
	});
}
