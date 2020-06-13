//
// Created by david on 13. 06. 2020..
//

#ifndef SURVIVE_AUDIOMASTER_H
#define SURVIVE_AUDIOMASTER_H

#include <AL/alc.h>
#include <AL/al.h>
#include <vector>

class AudioMaster
{
private:
    ALCdevice *m_Device;
    ALCcontext *m_Context;

    std::vector<ALuint> m_Buffers;

public:
    ALuint loadSound(const char *filename);

    ~AudioMaster();

private:
    static char *loadWav(const char *filename, std::uint8_t &channels,
                         std::int32_t &sampleRate, std::uint8_t &bitsPerSample, ALsizei &size);

    static ALenum getFormat(std::uint8_t channels, std::uint8_t bitsPerSample);

};


#endif //SURVIVE_AUDIOMASTER_H
