//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUISHADER_H
#define SURVIVE_GUISHADER_H


#include <glm/detail/type_mat.hpp>
#include "../shader/Shader.h"

class GuiShader : public Shader
{
private:
    constexpr static const char* VERTEX_FILE = "engine/shader/sources/GuiVertexShader.glsl";
    constexpr static const char* FRAGMENT_FILE = "engine/shader/sources/GuiFragmentShader.glsl";

    GLuint locationTransformationMatrix{};

    void getUniformLocations();

public:
    GuiShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;
};


#endif //SURVIVE_GUISHADER_H
