#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/DaeParser.h"
#include "engine/animations/animation/AnimatedObject.h"
#include "engine/animations/animation/Animator.h"
#include "engine/gui/GuiRenderer.h"
#include "engine/gaussianBlur/verticalBlur/VerticalBlurRenderer.h"
#include "engine/gaussianBlur/horizontalBlur/HorizontalBlurRenderer.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;

	DaeParser daeParser;
	TexturedModel texturedModel(daeParser.loadDae("res/character.xml", loader),
								Loader::loadTexture("res/character.png"));

	auto[rootJoint, numberOfJoints] = daeParser.getJointData();
	AnimatedObject object(rootJoint, numberOfJoints, texturedModel, glm::vec3{0, -10, -30}, glm::vec3{-90, 0, 0});

	Animator animator(daeParser.getAnimation(), object);

	Camera camera{};
	Light light(glm::vec3{10, 10, 10}, glm::vec3{1, 1, 1});

	Renderer3D renderer(light);
	renderer.addAnimatedObject(object);

	Model rawModel = loader.renderQuad();
	HorizontalBlurRenderer horizontalBlurRenderer(width / 4, height / 4);
	VerticalBlurRenderer verticalBlurRenderer(width / 4, height / 4);

	FrameBuffer fbo;
	GLuint texture = fbo.createTexture();
	TexturedModel model(rawModel, verticalBlurRenderer.getTexture().textureId());

	GuiRenderer guiRenderer;
	Entity entity(model, glm::vec3{0.5, 0.5, 0}, 0.5, 0.5);
	guiRenderer.addEntity(entity);

	while (display.isRunning())
	{
		Display::clearWindow();

		animator.update();

		fbo.bindFrameBuffer();
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		renderer.render(camera);
		FrameBuffer::unbindFrameBuffer();

		glBindVertexArray(rawModel.m_Vao);
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);

        horizontalBlurRenderer.render(Texture(texture));
		verticalBlurRenderer.render(Texture(horizontalBlurRenderer.getTexture()));

		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		renderer.render(camera);

		guiRenderer.render();

		display.update();
	}

	return 0;
}
