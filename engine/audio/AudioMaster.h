//
// Created by david on 13. 06. 2020..
//

#ifndef SURVIVE_AUDIOMASTER_H
#define SURVIVE_AUDIOMASTER_H

#include <AL/alc.h>
#include <AL/al.h>
#include <vector>
#include <glm/vec3.hpp>

namespace Survive
{
	class AudioMaster
	{
	private:
		static AudioMaster m_AudioMaster;

		ALCdevice *m_Device;
		ALCcontext *m_Context;

		std::vector<ALuint> m_Buffers;

		AudioMaster();

	public:
		ALint loadSound(const char *filename);

		~AudioMaster();

		static void setListenerData(glm::vec3 listenerPosition = glm::vec3{});

		static AudioMaster &getInstance();

	private:
		static char *loadWav(const char *filename, std::uint8_t &channels,
							 std::int32_t &sampleRate, std::uint8_t &bitsPerSample, ALsizei &size);

		static ALenum getFormat(std::uint8_t channels, std::uint8_t bitsPerSample);

		static void loadWavHelper(std::ifstream &reader, std::uint8_t &channels, std::int32_t &sampleRate,
								  std::uint8_t &bitsPerSample, ALsizei &size);

		static int convertToInt(const char *buffer, std::size_t len);
	};
}

#endif //SURVIVE_AUDIOMASTER_H
