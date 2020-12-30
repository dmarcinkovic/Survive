//
// Created by david on 06. 09. 2020..
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "JointTransform.h"

JointTransform::JointTransform(const glm::vec3 &position, const Quaternion &quaternion)
        : m_Position(position), m_Rotation(quaternion)
{

}

glm::mat4 JointTransform::getLocalTransform() const
{
    glm::mat4 matrix{1};
    matrix = glm::translate(matrix, m_Position);

//    std::cout << "Get local transform:\n";
//    std::cout << "Position: " << m_Position.x << ' ' << m_Position.y << ' ' << m_Position.z << "\n";
//
//    std::cout << "Matrix after translation: \n";
//
//    for (int i = 0; i < 4; ++i)
//	{
//    	for (int j = 0; j < 4; ++j)
//		{
//    		std::cout << m_Rotation.toRotationMatrix()[i][j] << ' ';
//		}
//    	std::cout << '\n';
//	}
//    std::cout << '\n';

    matrix *= m_Rotation.toRotationMatrix();

    return matrix;
}

JointTransform
JointTransform::interpolate(const JointTransform &frameA, const JointTransform &frameB, float progression)
{
    glm::vec3 position = interpolate(frameA.m_Position, frameB.m_Position, progression);
//    std::cout << "In joint transform interpolate method\n";
//    std::cout << frameA.m_Position.x << ' ' << frameA.m_Position.y << ' ' << frameA.m_Position.z << '\n';
//    std::cout << frameB.m_Position.x << ' ' << frameB.m_Position.y << ' ' << frameB.m_Position.z << '\n';
//    std::cout << position.x << ' ' << position.y << ' ' << position.z << '\n';
    Quaternion rotation = Quaternion::interpolate(frameA.m_Rotation, frameB.m_Rotation, progression);
    return JointTransform(position, rotation);
}

glm::vec3 JointTransform::interpolate(const glm::vec3 &start, const glm::vec3 &end, float progression)
{
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    return glm::vec3(x, y, z);
}

const glm::vec3 &JointTransform::position() const
{
    return m_Position;
}
