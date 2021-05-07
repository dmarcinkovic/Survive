//
// Created by david on 10. 06. 2020..
//

#ifndef SURVIVE_JOINT_H
#define SURVIVE_JOINT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Survive
{
	class Joint
	{
	private:
		std::vector<Joint> m_Children;
		int m_Index{};
		std::string m_Name;

		glm::mat4 m_AnimatedTransform{1};
		glm::mat4 m_InverseBindTransformation{1};

		glm::mat4 m_LocalBindTransform{};

	public:
		Joint() = default;

		Joint(std::string name, int index, const glm::mat4 &bindLocalTransform);

		void addChild(const Joint &childJoint);

		void calculateInverseBindTransform(const glm::mat4 &parentBindTransform);

		std::vector<Joint> &children();

		[[nodiscard]] const std::vector<Joint> &children() const;

		[[nodiscard]] const std::string &name() const;

		[[nodiscard]] const glm::mat4 &inverseBindTransform() const;

		void setAnimatedTransform(const glm::mat4 &animatedTransform);

		[[nodiscard]] const glm::mat4 &getAnimatedTransform() const;

		[[nodiscard]] int index() const;
	};
}

#endif //SURVIVE_JOINT_H
