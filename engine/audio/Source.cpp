//
// Created by david on 13. 06. 2020..
//

#include "Source.h"

Survive::Source::Source(float gain, float pitch)
{
	alGenSources(1, &m_Source);

	alSourcef(m_Source, AL_GAIN, gain);
	alSourcef(m_Source, AL_PITCH, pitch);
}

Survive::Source::~Source()
{
	stop();
	alDeleteSources(1, &m_Source);
}

void Survive::Source::play(ALint buffer) const
{
	stop();
	alSourcei(m_Source, AL_BUFFER, buffer);
	continuePlaying();
}

void Survive::Source::stop() const
{
	alSourceStop(m_Source);
}

void Survive::Source::pause() const
{
	alSourcePause(m_Source);
}

void Survive::Source::continuePlaying() const
{
	alSourcePlay(m_Source);
}

bool Survive::Source::isPlaying() const
{
	ALint value;
	alGetSourcei(m_Source, AL_SOURCE_STATE, &value);

	return value == AL_PLAYING;
}

void Survive::Source::setOnLoop(bool loop) const
{
	alSourcei(m_Source, AL_LOOPING, loop);
}

void Survive::Source::setPosition(const glm::vec3 &pos) const
{
	alSource3f(m_Source, AL_POSITION, pos.x, pos.y, pos.z);
}
