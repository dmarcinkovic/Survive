#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/particles/ParticleRenderer.h"
#include "engine/particles/ParticleSystem.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;

	ParticleRenderer particleRenderer;

	TexturedModel model(loader.renderQuadStrip(), Loader::loadTexture("res/particleAtlas.png"));
	ParticleModel particleModel(model, 4, 4);
	ParticleSystem particleSystem(100, 25, 0.3f, 4, 1);

	particleRenderer.addParticle(
			Particle(particleModel, glm::vec3{0, -10, -30}, glm::vec3{0, 1, 0}, 0.3f, 4));

	while (display.isRunning())
	{
		Display::clearWindow();

		std::vector<Particle> &particles = particleRenderer.getParticles(particleModel);
		particleSystem.generateParticles(glm::vec3{0, -10, -30}, particleModel, particles);

		particleRenderer.update(camera);

		particleRenderer.render(camera);

		display.update();
	}

	return 0;
}
