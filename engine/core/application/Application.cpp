//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "ContactPhysics2DListener.h"
#include "ContactPhysics3DListener.h"
#include "PhysicSystem.h"
#include "TerrainGenerator.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer, m_Registry), m_World2D(std::make_unique<b2World>(m_Gravity))
{
	auto terrain = m_Registry.create();
	m_Registry.emplace<TagComponent>(terrain, "terrain");
	m_Registry.emplace<Transform3DComponent>(terrain, glm::vec3{0, -10, -30}, glm::vec3{1, 1, 1});
	TexturedModel terrainModel(TerrainGenerator::generateTerrain(m_Loader, "assets/textures/heightmap.png"),
			m_Loader.loadTexture("assets/textures/blendMap.png"));
	std::vector<Texture> terrainTextures = m_Loader.loadAllTextures( {"assets/textures/dirt.png", "assets/textures/grass.jpeg", "assets/textures/rock.png", "assets/textures/flowers.png"});
	m_Registry.emplace<TerrainComponent>(terrain, terrainModel, terrainTextures);

	m_Registry.emplace<OutlineComponent>(terrain, false);

	m_ContactPhysics2DListener = std::make_unique<ContactPhysics2DListener>(m_Registry);
	m_ContactPhysics3DListener = std::make_unique<ContactPhysics3DListener>(m_Registry);

	m_Editor.addPlayButtonListener([this]() {
		m_RegistryUtil.store<RigidBody2DComponent, RigidBody3DComponent, SpriteSheetComponent, ParticleComponent>(
				m_Registry);
		System::init(m_Registry, m_EventHandler, m_World2D.get(), m_World3D, m_PhysicsCommon);

		m_World2D->SetContactListener(m_ContactPhysics2DListener.get());
		m_World3D->setEventListener(m_ContactPhysics3DListener.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent, RigidBody3DComponent, ParticleComponent>(
				m_Registry);

		m_World2D = std::make_unique<b2World>(m_Gravity);

		m_PhysicsCommon.destroyPhysicsWorld(m_World3D);
		m_World3D = m_PhysicsCommon.createPhysicsWorld();

		System::destroy(m_Registry);
	});

	m_World3D = m_PhysicsCommon.createPhysicsWorld();
}

void Survive::Application::run()
{
	while (m_Display.isRunning())
	{
		Display::clearWindow();

		m_Editor.handleKeyEvents(m_EventHandler);
		m_Editor.handleMouseDragging(m_Registry, m_Renderer, m_Camera);

		Editor::newFrame();
		Editor::dock();
		m_Editor.render(m_Registry, m_Renderer, m_Camera);

		if (m_Editor.isScenePlaying())
		{
			System::update(m_Registry, m_World2D.get(), m_World3D);
		}

		m_Display.update();
	}
}
