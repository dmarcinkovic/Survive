//
// Created by david on 05. 09. 2020..
//

#ifndef SURVIVE_QUATERNION_H
#define SURVIVE_QUATERNION_H

#include <glm/glm.hpp>

class Quaternion
{
private:
    float m_X, m_Y, m_Z, m_W;

public:
    Quaternion(float x, float y, float z, float w);

    void normalize();

    [[nodiscard]] glm::mat4 toRotationMatrix() const;

    static Quaternion fromMatrix(const glm::mat4 &matrix);

    static Quaternion interpolate(const Quaternion &a, const Quaternion &b, float blend);

    glm::vec4 getQuaternion() const;
};


#endif //SURVIVE_QUATERNION_H
