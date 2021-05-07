//
// Created by david on 13. 06. 2020..
//

#include <cstdint>
#include <iosfwd>
#include <fstream>
#include <iostream>
#include <cstring>

#include "AudioMaster.h"

ALuint Survive::AudioMaster::loadSound(const char *filename)
{
	m_Device = alcOpenDevice(nullptr);
	m_Context = alcCreateContext(m_Device, nullptr);
	alcMakeContextCurrent(m_Context);

	ALuint buffer;
	alGenBuffers(1, &buffer);

	m_Buffers.emplace_back(buffer);

	std::uint8_t channels;
	std::int32_t sampleRate;
	std::uint8_t bitsPerSample;
	ALsizei size;

	const char *wavFile = loadWav(filename, channels, sampleRate, bitsPerSample, size);

	ALenum format = getFormat(channels, bitsPerSample);
	alBufferData(buffer, format, wavFile, size, sampleRate);

	delete[] wavFile;

	return buffer;
}

Survive::AudioMaster::~AudioMaster()
{
	alDeleteBuffers(m_Buffers.size(), m_Buffers.data());
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);
}

char *Survive::AudioMaster::loadWav(const char *filename, uint8_t &channels,
									int32_t &sampleRate, uint8_t &bitsPerSample, ALsizei &size)
{
	std::ifstream reader(filename, std::ios::binary);

	if (!reader.is_open())
	{
		throw std::runtime_error("Could not open file");
	}

	loadWavHelper(reader, channels, sampleRate, bitsPerSample, size);

	char *data = new char[size];

	reader.read(data, size);
	reader.close();

	return data;
}

ALenum Survive::AudioMaster::getFormat(std::uint8_t channels, std::uint8_t bitsPerSample)
{
	if (channels == 1 && bitsPerSample == 8)
	{
		return AL_FORMAT_MONO8;
	} else if (channels == 1 && bitsPerSample == 16)
	{
		return AL_FORMAT_MONO16;
	} else if (channels == 2 && bitsPerSample == 8)
	{
		return AL_FORMAT_STEREO8;
	}
	return AL_FORMAT_STEREO16;
}

void Survive::AudioMaster::loadWavHelper(std::ifstream &reader, uint8_t &channels, int32_t &sampleRate,
										 uint8_t &bitsPerSample,
										 ALsizei &size)
{
	const int N = 4;
	char buffer[N];

	reader.read(buffer, N);

	if (std::strncmp(buffer, "RIFF", N) != 0)
	{
		throw std::runtime_error("Could not load wav file");
	}

	reader.read(buffer, N);
	reader.read(buffer, N);

	if (std::strncmp(buffer, "WAVE", N) != 0)
	{
		throw std::runtime_error("Could not load wav file");
	}

	reader.read(buffer, N);
	reader.read(buffer, N);
	reader.read(buffer, 2);

	reader.read(buffer, 2);
	channels = convertToInt(buffer, 2);

	reader.read(buffer, N);
	sampleRate = convertToInt(buffer, N);

	reader.read(buffer, N);
	reader.read(buffer, 2);

	reader.read(buffer, 2);
	bitsPerSample = convertToInt(buffer, 2);

	reader.read(buffer, N);

	if (std::strncmp(buffer, "data", N) != 0)
	{
		throw std::runtime_error("Did not found data");
	}

	reader.read(buffer, N);
	size = convertToInt(buffer, N);
}

int Survive::AudioMaster::convertToInt(const char *buffer, std::size_t len)
{
	std::int32_t number = 0;
	std::memcpy(&number, buffer, len);

	return number;
}

void Survive::AudioMaster::setListenerData(const glm::vec3 listenerPosition)
{
	alListener3f(AL_POSITION, listenerPosition.x, listenerPosition.y, listenerPosition.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
}
