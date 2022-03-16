//
// Created by david on 26. 02. 2022..
//

#include "Components.h"
#include "ScriptingSystem.h"

void Survive::ScriptingSystem::init(entt::registry &registry, EventHandler &eventHandler)
{
	auto view = registry.view<ScriptComponent>();

	for (entt::entity entity: view)
	{
		ScriptComponent &scriptComponent = view.get<ScriptComponent>(entity);

		auto &script = scriptComponent.script;

		if (script == nullptr)
		{
			script = scriptComponent.m_Plugin.createInstance(scriptComponent.m_PluginLocation);
		}

		initializeScriptingEntity(script, registry, entity, eventHandler);
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
	registry.view<ScriptComponent, TagComponent>().each([](ScriptComponent &script, TagComponent &) {
		if (script.script)
		{
			script.script->onDestroy();

			if (script.script->m_NeedRestore)
			{
				script.script->restoreEntity();
			}

			EventHandler::popKeyListener();
			EventHandler::popMouseListener();

			script.m_Plugin.deleteInstance(script.script);
		}
	});
}

void
Survive::ScriptingSystem::initializeScriptingEntity(ObjectBehaviour *script, entt::registry &registry,
													entt::entity entity, EventHandler &eventHandler)
{
	if (script != nullptr)
	{
		script->init(registry, entity, eventHandler);

		script->start();
		EventHandler::addMouseListener([=](int, int, double, double) {
			script->onMouseClick();
		});
		EventHandler::addKeyListener([=](int, int) {
			script->onKeyboardPressed();
		});
	}
}
