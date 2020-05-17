//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTSHADER_H
#define SURVIVE_OBJECTSHADER_H


#include "../shader/Shader.h"

class ObjectShader : public Shader
{
private:
    constexpr static const char *VERTEX_SHADER = "engine/shader/sources/ObjectVertexShader.glsl";
    constexpr static const char *FRAGMENT_SHADER = "engine/shader/sources/ObjectFragmentShader.glsl";

    GLuint m_LocationTransformationMatrix{};
    GLuint m_LocationProjectionMatrix{};
    GLuint m_LocationViewMatrix{};

    GLuint m_LocationLightColor{};
    GLuint m_LocationLightPos{};

public:
    ObjectShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

    void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

    void loadViewMatrix(const glm::mat4 &viewMatrix) const;

    void loadLight(const glm::vec3 &lightPos, const glm::vec3 &lightColor) const;

private:
    void loadUniformLocations() ;

};


#endif //SURVIVE_OBJECTSHADER_H
