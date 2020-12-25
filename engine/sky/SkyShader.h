//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYSHADER_H
#define SURVIVE_SKYSHADER_H


#include "../shader/Shader.h"

class SkyShader : public Shader
{
private:
	static constexpr const char* VERTEX_SHADER = "engine/shader/sources/SkyVertexShader.glsl";
	static constexpr const char* FRAGMENT_SHADER = "engine/shader/sources/SkyFragmentShader.glsl";

public:
	SkyShader();

private:
	void getUniformLocations();
};


#endif //SURVIVE_SKYSHADER_H
