//
// Created by david on 13. 06. 2020..
//

#ifndef SURVIVE_SOURCE_H
#define SURVIVE_SOURCE_H

#include <glm/glm.hpp>
#include <AL/al.h>

class Source
{
private:
	ALuint m_Source{};

public:
	explicit Source(const glm::vec3 &sourcePosition);

	~Source();

	void play(ALuint buffer) const;
};


#endif //SURVIVE_SOURCE_H
