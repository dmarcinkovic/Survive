#include <iostream>
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "ecs/entt.hpp"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Renderer3D renderer(light);

	struct TransformComponent {
		glm::vec3 pos;
	};

	struct RenderComponent {
		glm::vec3 color;
	};

	struct IdComponent {
		std::uint32_t id;

		IdComponent() = default;

		explicit IdComponent(std::uint32_t id)
			: id(id) {}
	};

	entt::registry registry;

	auto entity1 = registry.create();
	registry.emplace<TransformComponent>(entity1);
	registry.emplace<IdComponent>(entity1, 1);

	auto entity2 = registry.create();
	registry.emplace<RenderComponent>(entity2);
	registry.emplace<IdComponent>(entity2, 2);

	auto entity3 = registry.create();
	registry.emplace<RenderComponent>(entity3);
	registry.emplace<TransformComponent>(entity3);
	registry.emplace<IdComponent>(entity3, 3);

	auto group = registry.view<TransformComponent, IdComponent>();
	for (auto entity : group)
	{
		auto idComponent = group.get<IdComponent>(entity);
		std::cout << "Entity with ID: " << idComponent.id << '\n';
	}

	auto textures = Loader::loadTextures({"res/lamp_bloom.png", "res/lamp_bloom_emissive.png"});

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								textures["res/lamp_bloom.png"]);
	Object3D lamp(texturedModel, glm::vec3{-5, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});
	Object3D lamp2(texturedModel, glm::vec3{8, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});

	renderer.add3DObject(lamp);
	renderer.add3DObject(lamp2);

	Texture lampBloom(textures["res/lamp_bloom_emissive.png"]);
	renderer.addBloom(lamp);
	renderer.addBloom(lamp2);

	lamp.addBloomEffect(lampBloom);
	lamp2.addBloomEffect(lampBloom);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);

		display.update();
	}

	return 0;
}
