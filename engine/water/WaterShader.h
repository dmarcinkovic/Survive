//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERSHADER_H
#define SURVIVE_WATERSHADER_H


#include "../shader/Shader.h"

class WaterShader : public Shader
{
private:
	static constexpr const char* VERTEX_SHADER = "engine/shader/sources/WaterVertexShader.glsl";
	static constexpr const char* FRAGMENT_SHADER = "engine/shader/sources/WaterFragmentShader.glsl";

public:
	WaterShader();
};


#endif //SURVIVE_WATERSHADER_H
