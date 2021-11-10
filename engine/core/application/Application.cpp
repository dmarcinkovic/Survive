//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "PhysicSystem.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer), m_World2D(std::make_unique<b2World>(m_Gravity))
{
	auto cube = m_Registry.create();
	m_Registry.emplace<TagComponent>(cube, "cube");
	m_Registry.emplace<Transform3DComponent>(cube, glm::vec3{0, 2, -10}, glm::vec3{1.0f}, glm::vec3{0, 30, 0});
	m_Registry.emplace<RigidBodyComponent>(cube, false);
	m_Registry.emplace<Render3DComponent>(cube, TexturedModel(ObjParser::loadObj("res/cube.obj", m_Loader), Texture()));
	m_Registry.emplace<SpriteComponent>(cube, glm::vec4{0.8f, 0.3f, 0.1f, 1.0f});

	auto ground = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground, "ground");
	m_Registry.emplace<Transform3DComponent>(ground, glm::vec3{0, -2, -10}, glm::vec3{6, 0.5f, 8});
	m_Registry.emplace<RigidBodyComponent>(ground, false);
	m_Registry.emplace<Render3DComponent>(ground, TexturedModel(ObjParser::loadObj("res/cube.obj", m_Loader), Texture()));
	m_Registry.emplace<SpriteComponent>(ground, glm::vec4{0, 0.3f, 0.8f, 1.0f});

	m_Editor.addPlayButtonListener([this]() {
		PhysicSystem::init(m_Registry, m_World2D.get(), m_World3D);

		m_RegistryUtil.store<RigidBody2DComponent>(m_Registry);
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent>(m_Registry);
		m_World2D = std::make_unique<b2World>(m_Gravity);
	});

	rp3d::PhysicsWorld::WorldSettings settings;
	settings.gravity = rp3d::Vector3(0, -9.81, 0);
	m_World3D = m_PhysicsCommon.createPhysicsWorld(settings);

	rp3d::Vector3 position(0.0, 2, -10);
	rp3d::Quaternion orientation = rp3d::Quaternion::fromEulerAngles(0, glm::radians(30.0f), 0);
	rp3d::Transform transform(position, orientation);
	m_Body = m_World3D->createRigidBody(transform);
	m_Body->setType(rp3d::BodyType::DYNAMIC);
}

void Survive::Application::run()
{
	while (m_Display.isRunning())
	{
		Display::clearWindow();

		m_Editor.handleKeyEvents(m_EventHandler);

		Editor::newFrame();
		Editor::dock();
		m_Editor.render(m_Registry, m_Renderer, m_Camera);

		if (m_Editor.isScenePlaying())
		{
			PhysicSystem::update(m_Registry);

			float frameRate = ImGui::GetIO().Framerate;
			m_World2D->Step(1.0f / frameRate, 5, 5);
			m_World3D->update(1.0 / frameRate);
		}

		const rp3d::Transform &t = m_Body->getTransform();
		const rp3d::Vector3 &newPos = t.getPosition();
		const rp3d::Quaternion &q = t.getOrientation();

//		m_Registry.replace<Transform3DComponent>(cube, glm::vec3{newPos.x, newPos.y, newPos.z});

		m_Display.update();
	}
}
