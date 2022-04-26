//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "ContactListener.h"
#include "PhysicSystem.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer, m_Registry), m_World2D(std::make_unique<b2World>(m_Gravity))
{
	m_Camera.position = glm::vec3{0, 0, 7};

	auto box1 = m_Registry.create();
	m_Registry.emplace<TagComponent>(box1, "box1");
	m_Registry.emplace<OutlineComponent>(box1, false);
	m_Registry.emplace<Transform3DComponent>(box1, glm::vec3{0, 4, -10});
	m_Registry.emplace<SpriteComponent>(box1, glm::vec4{0.8f, 0.1f, 0.3f, 1.0f});
	m_Registry.emplace<RigidBody3DComponent>(box1, rp3d::BodyType::STATIC, 1);
	m_Registry.emplace<Render3DComponent>(box1, TexturedModel(ObjParser::loadObj("assets/models/cube.obj", m_Loader),
															  Texture()));

	auto box2 = m_Registry.create();
	m_Registry.emplace<TagComponent>(box2, "box2");
	m_Registry.emplace<OutlineComponent>(box2, false);
	m_Registry.emplace<Transform3DComponent>(box2, glm::vec3{4, 4, -10});
	m_Registry.emplace<SpriteComponent>(box2, glm::vec4{0.1f, 0.4f, 0.7f, 1.0f});
	m_Registry.emplace<RigidBody3DComponent>(box2, rp3d::BodyType::DYNAMIC, 1);
	m_Registry.emplace<Render3DComponent>(box2, TexturedModel(ObjParser::loadObj("assets/models/cube.obj", m_Loader),
															  Texture()));
	const rp3d::Vector3 anchorPointWorldSpace = 0.5 * (rp3d::Vector3{4, 4, -10} + rp3d::Vector3{0, 4, -10}) - rp3d::Vector3(0, 2, 0);
	const rp3d::Vector3 hingeAxisWorldSpace(0, 0, 1);
	HingeJoint3DComponent hinge;
	hinge.connectedBody = box2;
	hinge.connectedBodyName = "box2";
	hinge.jointInfo.anchorPointWorldSpace = anchorPointWorldSpace;
	hinge.jointInfo.rotationAxisWorld = hingeAxisWorldSpace;
	hinge.jointInfo.isCollisionEnabled = false;
	hinge.jointInfo.motorSpeed = 10.0f;
	hinge.jointInfo.isMotorEnabled = true;
	m_Registry.emplace<HingeJoint3DComponent>(box1, hinge);

	m_ContactListener = std::make_unique<ContactListener>(m_Registry);

	m_Editor.addPlayButtonListener([this]() {
		m_RegistryUtil.store<RigidBody2DComponent, RigidBody3DComponent, SpriteSheetComponent>(m_Registry);
		System::init(m_Registry, m_EventHandler, m_World2D.get(), m_World3D, m_PhysicsCommon);

		m_World2D->SetContactListener(m_ContactListener.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent, RigidBody3DComponent>(m_Registry);

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
