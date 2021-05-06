#include "Loader.h"
#include "ObjParser.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer3D.h"
#include "Display.h"
#include "entt.hpp"

int main()
{
	using namespace Survive;

	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});
	Renderer3D renderer(light);

	entt::registry registry;

	auto lamp = registry.create();
	registry.emplace<RenderComponent>(lamp, TexturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
														  Loader::loadTexture("res/lamp_bloom.png")));
	registry.emplace<Transform3DComponent>(lamp, glm::vec3{0, -6, -15}, glm::vec3{0.05f}, glm::vec3{0, -90, 0,});
	registry.emplace<RigidBodyComponent>(lamp, false);
	registry.emplace<IdComponent>(lamp, 2);
	registry.emplace<BloomComponent>(lamp, Loader::loadTexture("res/lamp_bloom_emissive.png"), 3.0f);
	renderer.addShadow(registry, lamp);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(registry, camera);

		display.update();
	}

	return 0;
}
