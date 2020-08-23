//
// Created by david on 12. 08. 2020..
//

#ifndef SURVIVE_ANIMATIONSHADER_H
#define SURVIVE_ANIMATIONSHADER_H


#include "../shader/Shader.h"

class AnimationShader : public Shader
{
private:
    static constexpr const char* VERTEX_SHADER = "engine/shader/sources/AnimationVertexShader.glsl";
    static constexpr const char* FRAGMENT_SHADER = "engine/shader/sources/AnimationFragmentShader.glsl";

    GLuint m_LocationTransformationMatrix{};
    GLuint m_LocationViewMatrix{};
    GLuint m_LocationProjectionMatrix{};

    GLuint m_LocationLightPosition{};
    GLuint m_LocationLightColor{};

public:
    AnimationShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

    void loadViewMatrix(const glm::mat4 &viewMatrix) const;

    void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

    void loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor) const;

private:
    void loadUniformLocations();
};


#endif //SURVIVE_ANIMATIONSHADER_H
