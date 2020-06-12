//
// Created by david on 13. 06. 2020..
//

#include <cstdint>
#include "AudioMaster.h"

ALuint AudioMaster::loadSound(const char *filename)
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

    

    return 0;
}

AudioMaster::~AudioMaster()
{
    alDeleteBuffers(m_Buffers.size(), m_Buffers.data());
}

char *AudioMaster::loadWav(const char *filename, uint8_t &channels, int32_t &sampleRate, uint8_t &bitsPerSample,
                           ALsizei &size)
{

}
