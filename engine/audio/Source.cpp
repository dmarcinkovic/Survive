//
// Created by david on 13. 06. 2020..
//

#include "Source.h"

Source::Source(float gain, float pitch)
{
	alGenSources(1, &m_Source);

	alSourcef(m_Source, AL_GAIN, gain);
	alSourcef(m_Source, AL_PITCH, pitch);
}

Source::~Source()
{
	stop();
	alDeleteSources(1, &m_Source);
}

void Source::play(ALuint buffer) const
{
	stop();
	alSourcei(m_Source, AL_BUFFER, buffer);
	continuePlaying();
}

void Source::stop() const
{
	alSourceStop(m_Source);
}

void Source::pause() const
{
	alSourcePause(m_Source);
}

void Source::continuePlaying() const
{
	alSourcePlay(m_Source);
}

bool Source::isPlaying() const
{
	ALint value;
	alGetSourcei(m_Source, AL_SOURCE_STATE, &value);

	return value == AL_PLAYING;
}

void Source::setOnLoop(bool loop) const
{
	alSourcei(m_Source, AL_LOOPING, loop);
}

void Source::setPosition(const glm::vec3 &pos) const
{
	alSource3f(m_Source, AL_POSITION, pos.x, pos.y, pos.z);
}
