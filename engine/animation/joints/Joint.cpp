//
// Created by david on 10. 06. 2020..
//

#include "Joint.h"

Joint::Joint(std::string name, int index, glm::mat4 inverseTransformation)
    : m_Name(std::move(name)), m_Index(index), m_InverseTransformation(inverseTransformation)
{

}
