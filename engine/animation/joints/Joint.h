//
// Created by david on 10. 06. 2020..
//

#ifndef SURVIVE_JOINT_H
#define SURVIVE_JOINT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

class Joint
{
private:
    std::vector<Joint> m_Children;
    int m_Index;
    std::string m_Name;

    glm::mat4 m_InverseTransformation{};

public:
    Joint(std::string name, int index, glm::mat4 inverseTransformation);
};


#endif //SURVIVE_JOINT_H
