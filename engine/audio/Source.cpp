//
// Created by david on 13. 06. 2020..
//

#include "Source.h"

Source::Source(const glm::vec3 &sourcePosition)
{
	alGenSources(1, &m_Source);
	alSourcef(m_Source, AL_GAIN, 1);
	alSourcef(m_Source, AL_PITCH, 1);
	alSource3f(m_Source, AL_POSITION, sourcePosition.x, sourcePosition.y, sourcePosition.z);
}

Source::~Source()
{
	alDeleteSources(1, &m_Source);
}

void Source::play(ALuint buffer) const
{
	alSourcei(m_Source, AL_BUFFER, buffer);
	alSourcePlay(m_Source);
}
