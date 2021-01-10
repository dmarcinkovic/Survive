#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/gui/GuiRenderer.h"
#include "engine/gaussianBlur/BlurRenderer.h"
#include "engine/parser/ObjParser.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;

	Camera camera{};
	Light light(glm::vec3{10, 10, 10}, glm::vec3{1, 1, 1});

	Renderer3D renderer(light);

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								Loader::loadTexture("res/lamp_bloom.png"));
	Object3D lamp(texturedModel, glm::vec3{0, -20, -50}, glm::vec3{0,-90,0}, false, glm::vec3{0.2f, 0.2f, 0.2f});

	renderer.add3DObject(lamp);

	HorizontalBlurRenderer horizontalBlurRenderer(width / 4, height / 4);
	VerticalBlurRenderer verticalBlurRenderer(width / 4, height / 4);
	TexturedModel model(loader.renderQuad(), verticalBlurRenderer.getTexture().textureId());

	Texture lampBloom(Loader::loadTexture("res/lamp_bloom_emissive.png"));
	Model quadModel = loader.renderQuad();

	GuiRenderer guiRenderer;
	Entity entity(model, glm::vec3{0.5, 0.5, 0}, glm::vec3{0.5, 0.5, 1});
	guiRenderer.addEntity(entity);

	while (display.isRunning())
	{
		Display::clearWindow();

		glBindVertexArray(quadModel.m_Vao);
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);

		horizontalBlurRenderer.render(lampBloom, quadModel);
		verticalBlurRenderer.render(horizontalBlurRenderer.getTexture(), quadModel);

		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		renderer.render(camera);

		guiRenderer.render();

		display.update();
	}

	return 0;
}
