//
// Created by david on 05. 09. 2020..
//

#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
		: m_X(x), m_Y(y), m_Z(z), m_W(w)
{
	normalize();
}

void Quaternion::normalize()
{
	auto magnitude = static_cast<float>(std::sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W + m_W));
	m_X /= magnitude;
	m_Y /= magnitude;
	m_Z /= magnitude;
	m_W /= magnitude;
}

glm::mat4 Quaternion::toRotationMatrix() const
{
	float xx = m_X * m_X;
	float xy = m_X * m_Y;
	float xz = m_X * m_Z;
	float xw = m_X * m_W;

	float yy = m_Y * m_Y;
	float yz = m_Y * m_Z;
	float yw = m_Y * m_W;

	float zz = m_Z * m_Z;
	float zw = m_Z * m_W;

	glm::mat4 m{};
	m[0][0] = 1 - 2 * (yy + zz);
	m[0][1] = 2 * (xy - zw);
	m[0][2] = 2 * (xz + yw);
	m[0][3] = 0;
	m[1][0] = 2 * (xy + zw);
	m[1][1] = 1 - 2 * (xx + zz);
	m[1][2] = 2 * (yz - xw);
	m[1][3] = 0;
	m[2][0] = 2 * (xz - yw);
	m[2][1] = 2 * (yz + xw);
	m[2][2] = 1 - 2 * (xx + yy);
	m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;

	return m;
}

Quaternion Quaternion::fromMatrix(const glm::mat4 &matrix)
{
	float w, x, y, z;
	float diagonal = matrix[0][0] + matrix[1][1] + matrix[2][2];
	if (diagonal > 0)
	{
		auto w4 = static_cast<float> (std::sqrt(diagonal + 1.0f) * 2.0f);
		w = w4 / 4.0f;
		x = (matrix[2][1] - matrix[1][2]) / w4;
		y = (matrix[0][2] - matrix[2][0]) / w4;
		z = (matrix[1][0] - matrix[0][1]) / w4;
	} else if ((matrix[0][0] > matrix[1][1]) && (matrix[0][0] > matrix[2][2]))
	{
		auto x4 = static_cast<float>(std::sqrt(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]) * 2.0f);
		w = (matrix[2][1] - matrix[1][2]) / x4;
		x = x4 / 4.0f;
		y = (matrix[0][1] + matrix[1][0]) / x4;
		z = (matrix[0][2] + matrix[2][0]) / x4;
	} else if (matrix[1][1] > matrix[2][2])
	{
		auto y4 = static_cast<float>(std::sqrt(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 2.0f);
		w = (matrix[0][2] - matrix[2][0]) / y4;
		x = (matrix[0][1] + matrix[1][0]) / y4;
		y = y4 / 4.0f;
		z = (matrix[1][2] + matrix[2][1]) / y4;
	} else
	{
		auto z4 = static_cast<float>(std::sqrt(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 2.0f);
		w = (matrix[1][0] - matrix[0][1]) / z4;
		x = (matrix[0][2] + matrix[2][0]) / z4;
		y = (matrix[1][2] + matrix[2][1]) / z4;
		z = z4 / 4.0f;
	}
	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::interpolate(const Quaternion &a, const Quaternion &b, float blend)
{
	Quaternion result(0, 0, 0, 1);
	float dot = a.m_W * b.m_W + a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z;
	float blendI = 1.0f - blend;
	if (dot < 0)
	{
		result.m_W = blendI * a.m_W + blend * -b.m_W;
		result.m_X = blendI * a.m_X + blend * -b.m_X;
		result.m_Y = blendI * a.m_Y + blend * -b.m_Y;
		result.m_Z = blendI * a.m_Z + blend * -b.m_Z;
	} else
	{
		result.m_W = blendI * a.m_W + blend * b.m_W;
		result.m_X = blendI * a.m_X + blend * b.m_X;
		result.m_Y = blendI * a.m_Y + blend * b.m_Y;
		result.m_Z = blendI * a.m_Z + blend * b.m_Z;
	}
	result.normalize();
	return result;
}
