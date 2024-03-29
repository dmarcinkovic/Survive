//
// Created by david on 06. 09. 2020..
//

#include <glm/gtc/matrix_transform.hpp>

#include "JointTransform.h"

Survive::JointTransform::JointTransform(const glm::vec3 &position, const Quaternion &quaternion)
		: m_Position(position), m_Rotation(quaternion)
{
}

glm::mat4 Survive::JointTransform::getLocalTransform() const
{
	glm::mat4 matrix{1};
	matrix = glm::translate(matrix, m_Position);
	matrix *= m_Rotation.toRotationMatrix();

	return matrix;
}

Survive::JointTransform
Survive::JointTransform::interpolate(const JointTransform &frameA, const JointTransform &frameB, float progression)
{
	glm::vec3 position = interpolate(frameA.m_Position, frameB.m_Position, progression);
	Quaternion rotation = Quaternion::interpolate(frameA.m_Rotation, frameB.m_Rotation, progression);
	return JointTransform(position, rotation);
}

glm::vec3 Survive::JointTransform::interpolate(const glm::vec3 &start, const glm::vec3 &end, float progression)
{
	float x = start.x + (end.x - start.x) * progression;
	float y = start.y + (end.y - start.y) * progression;
	float z = start.z + (end.z - start.z) * progression;
	return glm::vec3(x, y, z);
}

const glm::vec3 &Survive::JointTransform::position() const
{
	return m_Position;
}
