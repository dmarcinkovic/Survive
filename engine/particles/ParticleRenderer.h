//
// Created by david on 11. 02. 2021..
//

#ifndef SURVIVE_PARTICLERENDERER_H
#define SURVIVE_PARTICLERENDERER_H


#include <unordered_map>

#include "ParticleShader.h"
#include "../camera/Camera.h"
#include "../texture/TexturedModel.h"
#include "Particle.h"

class ParticleRenderer
{
private:
	constexpr static int MAX_INSTANCES = 10'000;
	int m_Pointer{};
	std::unordered_map<TexturedModel, std::vector<Particle>, TextureHash> m_Particles;

	ParticleShader m_Shader;

public:
	void render(const Camera &camera);

private:
	void prepare();

	void finish();

	static void enableBlending();
};


#endif //SURVIVE_PARTICLERENDERER_H
