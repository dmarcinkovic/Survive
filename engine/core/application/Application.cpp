//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "PhysicSystem.h"
#include "Animator.h"
#include "TerrainGenerator.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer), m_World(std::make_unique<b2World>(m_Gravity))
{
	auto character = m_Registry.create();
	m_Registry.emplace<TagComponent>(character, "character");
	m_Registry.emplace<Transform3DComponent>(character, glm::vec3{-6, -3, -15});
	m_Registry.emplace<ShadowComponent>(character, true);

	m_Registry.emplace<Render3DComponent>(character,
										  TexturedModel(m_DaeParser.loadDae("assets/models/character.dae", m_Loader),
														m_Loader.loadTexture("assets/textures/character.png")));

	auto[rootJoint, numberOfJoints] = m_DaeParser.getJointData();
	m_Registry.emplace<AnimationComponent>(character, rootJoint, numberOfJoints);

	auto lamp = m_Registry.create();
	m_Registry.emplace<TagComponent>(lamp, "lamp");
	m_Registry.emplace<Transform3DComponent>(lamp, glm::vec3{-1, -4.5, -15}, glm::vec3{0.05f}, glm::vec3{0, 45, 0});
	m_Registry.emplace<Render3DComponent>(lamp,
										  TexturedModel(ObjParser::loadObj("assets/models/lamp_bloom.obj", m_Loader),
														m_Loader.loadTexture("assets/textures/lamp_bloom.png")));
	m_Registry.emplace<BloomComponent>(lamp, m_Loader.loadTexture("assets/textures/lamp_bloom_emissive.png"), 3.0f);
	m_Registry.emplace<ShadowComponent>(lamp, true);

	auto soccer = m_Registry.create();
	m_Registry.emplace<TagComponent>(soccer, "soccer");
	m_Registry.emplace<Transform3DComponent>(soccer, glm::vec3{4, 2, -10});
	m_Registry.emplace<Render3DComponent>(soccer,
										  TexturedModel(ObjParser::loadObj("assets/models/soccer.obj", m_Loader),
														m_Loader.loadTexture("assets/textures/ball.png")));
	m_Registry.emplace<MaterialComponent>(soccer, false, true, m_Loader.loadTexture("assets/textures/ball_normal.png"));
	m_Registry.emplace<ShadowComponent>(soccer, true);

	auto skybox = m_Registry.create();
	m_Registry.emplace<TagComponent>(skybox, "skybox");
	std::vector<const char *> faces{"assets/skybox/right.png", "assets/skybox/left.png", "assets/skybox/top.png",
									"assets/skybox/bottom.png", "assets/skybox/front.png", "assets/skybox/back.png"};
	m_Registry.emplace<Render3DComponent>(skybox, TexturedModel(m_Loader.renderCube(), m_Loader.loadCubeMap(faces)));
	m_Registry.emplace<Transform3DComponent>(skybox, glm::vec3{0}, glm::vec3{500});

	m_Renderer.addSkyboxEntity(skybox);

	m_Editor.addPlayButtonListener([this]() {
		m_RegistryUtil.store<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		PhysicSystem::init(m_Registry, m_World.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		m_World = std::make_unique<b2World>(m_Gravity);
	});
}

void Survive::Application::run()
{
	Animator animator(m_DaeParser.getAnimation());

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
			System::update(m_Registry, m_World.get());
			animator.update(m_Registry);
		}

		m_Display.update();
	}
}
