//
// Created by david on 10. 06. 2020..
//

#ifndef SURVIVE_JOINT_H
#define SURVIVE_JOINT_H

#include <string>
#include <vector>

class Joint
{
private:
    std::vector<Joint> children;
    float weight;
    int index;
    std::string name;

public:
    Joint(std::string name, int index);
};


#endif //SURVIVE_JOINT_H
